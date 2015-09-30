#include "fingered_private.h"

Fingered_User *
fingered_user_new(const char *user,
                  size_t len,
                  Ecore_Con_Client *cl)
{
   Fingered_User *fu;

   fu = calloc(1, sizeof(Fingered_User));
   if (!fu)
     {
        ERR("Failed to allocate Fingered_User structure");
        return NULL;
     }

   fu->user = strndup(user, len);
   if (!fu->user)
     {
        ERR("Failed to duplicate user string");
        goto free_fu;
     }

   fu->cl = cl;

#define _EV(_a, _b, _c, _d)                                                    \
   _a = ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_##_b,                   \
                                fingered_event_##_c, _d)
   _EV(fu->ev.write, WRITE, write, fu);
#undef _EV
   return fu;

free_fu:
   free(fu);
   return NULL;
}

Eina_Bool
fingered_user_send(Fingered_User *fu,
                   void *data,
                   size_t len)
{
   ecore_con_client_send(fu->cl, data, len);
   fu->queued += len;
   ecore_con_client_flush(fu->cl);
   return EINA_TRUE;
}

Eina_Bool
fingered_user_free(Fingered_User *fu)
{
   DBG("fu[%p]", fu);

   fu->delete_me = EINA_TRUE;
   if (fu->queued)
     return EINA_TRUE;

   DBG("Deleting fu[%p] cl[%p]", fu, fu->cl);
   ecore_con_client_send(fu->cl, "\r\n", 2);
   ecore_con_client_flush(fu->cl);
   ecore_con_client_del(fu->cl);
   ecore_event_handler_del(fu->ev.write);
   free(fu);
   return EINA_TRUE;
}
