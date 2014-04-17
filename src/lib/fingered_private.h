#include <Fingered.h>

typedef struct _Fingered
{
   Ecore_Con_Server *svr;

   struct
   {
      Ecore_Event_Handler *add,
                          *del,
                          *data;
   } ev;
} Fingered;

extern int _fingered_log_dom_global;

#define ERR(...) EINA_LOG_DOM_ERR(_fingered_log_dom_global, __VA_ARGS__)
#define DBG(...) EINA_LOG_DOM_DBG(_fingered_log_dom_global, __VA_ARGS__)
#define NFO(...) EINA_LOG_DOM_INFO(_fingered_log_dom_global, __VA_ARGS__)
#define WRN(...) EINA_LOG_DOM_WARN(_fingered_log_dom_global, __VA_ARGS__)
#define CRI(...) EINA_LOG_DOM_CRIT(_fingered_log_dom_global, __VA_ARGS__)


Eina_Bool fingered_event_add(void *data, int type, void *ev);
Eina_Bool fingered_event_del(void *data, int type, void *ev);
Eina_Bool fingered_event_data(void *data, int type, void *ev);
