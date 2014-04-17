#include <Fingered.h>

int main(int argc EINA_UNUSED, char **argv EINA_UNUSED)
{
   Fingered *f;

   fingered_init();

   f = fingered_new();

   ecore_main_loop_begin();

   fingered_shutdown();
   return 0;
}
