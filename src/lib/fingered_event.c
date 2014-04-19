#include <ctype.h>
#include "fingered_private.h"

void
_fingered_event_fake_free(void *d1 EINA_UNUSED,
                          void *d2 EINA_UNUSED)
{}


Eina_Bool
fingered_event_write(void *data,
                     int type EINA_UNUSED,
                     void *ev)
{
   Ecore_Con_Event_Client_Write *write;
   Fingered_User *fu;

   DBG("data[%p] ev[%p]", data, ev);

   write = ev;
   fu = data;

   fu->queued -= write->size;

   if (!fu->delete_me)
     return EINA_TRUE;

   fingered_user_free(fu);

   return EINA_TRUE;
}

Eina_Bool
fingered_event_add(void *data,
                   int type EINA_UNUSED,
                   void *ev)
{
   Ecore_Con_Event_Client_Add *add;

   DBG("data[%p] ev[%p]", data, ev);

   add = ev;
   ecore_con_client_timeout_set(add->client, 30);
   return EINA_TRUE;
}


Eina_Bool
fingered_event_del(void *data,
                   int type EINA_UNUSED,
                   void *ev)
{
   Ecore_Con_Event_Client_Del *del;

   DBG("data[%p] ev[%p]", data, ev);
   del = ev;
   return EINA_TRUE;
}


Eina_Bool
fingered_event_data(void *data,
                    int type EINA_UNUSED,
                    void *ev)
{
   Ecore_Con_Event_Client_Data *event;
   Fingered *f;
   Fingered_User *fu;
   char *n,
        *r,
        *p;
   char fmt[128];
   size_t l;

   DBG("data[%p] ev[%p]", data, ev);

   f = data;
   event = ev;

   snprintf(fmt, sizeof(fmt),
            "Received %i bytes from client:\n"
            ">>>>>\n"
            "%%.%is\n"
            ">>>>>\n",
            event->size, event->size);
   printf(fmt, event->data);

   n = memchr(event->data, '\n', event->size);
   if (!n)
     {
        l = event->size;
        goto check_user;
     }

   r = memchr(event->data, '\r', event->size);
   if (!r)
     {
        l = n - (char *)event->data;
        goto check_user;
     }

   l = r - (char *)event->data;

check_user:
   for (p = event->data; (size_t)(p - (char *)event->data) < l; p++)
     {
        if (isalnum(*p))
          continue;
        ERR("Invalid user requested");
        ecore_con_client_del(event->client);
        return EINA_TRUE;
     }

   fu = fingered_user_new(event->data, l, event->client);
   if (!fu)
     return EINA_TRUE;

   DBG("fu[%p]", fu);
   ecore_event_add(FINGERED_EVENT_USER, fu, _fingered_event_fake_free, f);

   return EINA_TRUE;
}
