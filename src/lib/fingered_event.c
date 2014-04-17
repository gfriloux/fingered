#include "fingered_private.h"

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
   char fmt[128];

   DBG("data[%p] ev[%p]", data, ev);

   event = ev;

   snprintf(fmt, sizeof(fmt),
            "Received %i bytes from client:\n"
            ">>>>>\n"
            "%%.%is\n"
            ">>>>>\n",
            event->size, event->size);
   printf(fmt, event->data);


   return EINA_TRUE;
}
