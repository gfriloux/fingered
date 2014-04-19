#include <Eina.h>
#include <Ecore.h>
#include <Ecore_Con.h>

extern int FINGERED_EVENT_USER;

typedef struct _Fingered Fingered;

typedef struct _Fingered_User
{
   Fingered *f;

   const char *user;
   Ecore_Con_Client *cl;

   size_t queued;
   Eina_Bool delete_me;

   struct
   {
      Ecore_Event_Handler *write;
   } ev;
} Fingered_User;

int fingered_init(void);
int fingered_shutdown(void);
Fingered * fingered_new(void);

Eina_Bool fingered_user_send(Fingered_User *fu, void *data, size_t len);
Eina_Bool fingered_user_free(Fingered_User *fu);
