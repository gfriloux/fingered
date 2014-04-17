#include "fingered_private.h"

static int _fingered_init_count = 0;
int _fingered_log_dom_global = -1;

int FINGERED_EVENT_USER = 0;


Fingered *
fingered_new(void)
{
   Fingered *f;

   f = calloc(1, sizeof(Fingered));
   if (!f)
     {
        ERR("Failed to allocated Fingered structure");
        return NULL;
     }

   f->svr = ecore_con_server_add(ECORE_CON_REMOTE_TCP, "0.0.0.0", 79, f);
   if (!f->svr)
     goto free_f;

#define _EV(_a, _b, _c, _d)                                                    \
   _a = ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_##_b,                   \
                                fingered_event_##_c, _d)
   _EV(f->ev.add, ADD, add, f);
   _EV(f->ev.del, DEL, del, f);
   _EV(f->ev.data, DATA, data, f);
#undef _EV

   return f;

free_f:
   free(f);
   return NULL;
}

int
fingered_init(void)
{
   if (++_fingered_init_count != 1)
     return _fingered_init_count;

   if (!eina_init())
     {
        fprintf(stderr, "Fingered can not initialize Eina\n");
        return --_fingered_init_count;
     }

   _fingered_log_dom_global = eina_log_domain_register("libfingered",
                                                       EINA_COLOR_RED);
   if (_fingered_log_dom_global < 0)
     {
        EINA_LOG_ERR("Fingered can not create a general log domain");
        goto shutdown_eina;
     }

   if (!ecore_init())
     {
        ERR("Can not initialize Ecore");
        goto unregister_log_domain;
     }

   if (!ecore_con_init())
     {
        ERR("Can not initialize Ecore_Con");
        goto shutdown_ecore;
     }

   FINGERED_EVENT_USER = ecore_event_type_new();

   return _fingered_log_dom_global;

shutdown_ecore:
   ecore_shutdown();
unregister_log_domain:
   eina_log_domain_unregister(_fingered_log_dom_global);
   _fingered_log_dom_global = -1;
shutdown_eina:
   eina_shutdown();
   return --_fingered_init_count;
}

int
fingered_shutdown(void)
{
   if (_fingered_init_count <= 0)
     {
        fprintf(stderr, "Fingered init count not greater than 0 in shutdown.");
        return 0;
     }

   if (--_fingered_init_count != 0)
     return _fingered_init_count;

   ecore_con_shutdown();
   ecore_shutdown();
   eina_log_domain_unregister(_fingered_log_dom_global);
   _fingered_log_dom_global = -1;
   eina_shutdown();
   return _fingered_init_count;
}
