#define _GNU_SOURCE
#include <Fingered.h>

#include <unistd.h>
#include <pwd.h>
#define BUFLEN 4096

int _main_log_dom_global = -1;

#define ERR(...) EINA_LOG_DOM_ERR(_main_log_dom_global, __VA_ARGS__)
#define DBG(...) EINA_LOG_DOM_DBG(_main_log_dom_global, __VA_ARGS__)
#define NFO(...) EINA_LOG_DOM_INFO(_main_log_dom_global, __VA_ARGS__)
#define WRN(...) EINA_LOG_DOM_WARN(_main_log_dom_global, __VA_ARGS__)
#define CRI(...) EINA_LOG_DOM_CRIT(_main_log_dom_global, __VA_ARGS__)

typedef struct _User
{
   Fingered_User *fu;

   uid_t    uid;
   gid_t    gid;
   char    *dir;
} User;


void
_user_execute(User *u,
              const char *s)
{
   DBG("u[%p] s[%s]", u, s);
}

void
_user_read(User *u,
           const char *s)
{
   Eina_File *ef;
   size_t l;
   void *d;

   DBG("u[%p] s[%s]", u, s);

   ef = eina_file_open(s, EINA_FALSE);
   if (!ef)
     {
        ERR("Failed to open %s", s);
        goto user_read_end;
     }

   l = eina_file_size_get(ef);
   if (l > 10240)
     {
        WRN("File is over 10KB! We will only send first 10KB!");
        l = 10240;
     }

   d = eina_file_map_all(ef, EINA_FILE_SEQUENTIAL);
   if (!d)
     {
        ERR("Failed to mmap file %s", s);
        goto close_file;
     }

   fingered_user_send(u->fu, d, l);

close_file:
   eina_file_close(ef);
user_read_end:
   fingered_user_free(u->fu);
}

void
_user_check(User *u)
{
   char *s;
   int r;

   DBG("u[%p][%s]", u, u->fu->user);

   s = calloc(1, strlen(u->dir) + 9);
   sprintf(s, "%s/.finger", u->dir);

   DBG("Checking for finger file %s", s);

   r = access(s, R_OK);
   if (r)
     goto free_s;

   r = access(s, X_OK);
   if (r)
     _user_read(u, s);
   else
     _user_execute(u, s);

free_s:
   free(s);
   fingered_user_free(u->fu);
   free(u->dir);
   free(u);
}


Eina_Bool
_user_event(void *data,
            int type EINA_UNUSED,
            void *ev)
{
   Fingered_User *fu;
   User *u = NULL;
   struct passwd pw, *pwp;
   char buf[BUFLEN];
   int r;


   DBG("data[%p] ev[%p]", data, ev);

   fu = ev;

   setpwent();
   while (1)
     {
        r = getpwent_r(&pw, buf, BUFLEN, &pwp);
        if (r)
          break;

        if (strcmp(pwp->pw_name, fu->user))
          continue;

        u = calloc(1, sizeof(User));
        if (!u)
          {
             ERR("Failed to allocate User structure.");
             break;
          }

        u->fu = fu;
        u->uid = pwp->pw_uid;
        u->gid = pwp->pw_gid;
        u->dir = strdup(pwp->pw_dir);
        if (!u->dir)
          {
             ERR("Failed to allocate home directory.");
             free(u);
             u = NULL;
          }

        break;
     }
   endpwent();

   if (u)
     _user_check(u);

   return EINA_TRUE;
}


int main(int argc EINA_UNUSED, char **argv EINA_UNUSED)
{
   Fingered *f;

   fingered_init();

   _main_log_dom_global = eina_log_domain_register("fingered",
                                                   EINA_COLOR_YELLOW);
   if (_main_log_dom_global < 0)
     {
        EINA_LOG_ERR("Fingered can not create a general log domain");
        return 1;
     }

   f = fingered_new();
   if (!f)
     {
        ERR("Failed to create new fingered server.");
        return 1;
     }

   ecore_event_handler_add(FINGERED_EVENT_USER, _user_event, NULL);


   ecore_main_loop_begin();

   fingered_shutdown();
   return 0;
}
