#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

void make_random_string(char *buff, size_t copylen)
{
   assert(copylen>1);

   int fh = open("/dev/urandom", O_RDONLY);
   if (fh)
   {
      size_t rcount = read(fh, buff, copylen);
      if (rcount==copylen)
      {
         unsigned char *p = (unsigned char*)buff;
         unsigned char *end = p + copylen;
         while (p<end)
         {
            *p %= 62;
            
            if (*p < 10)
               *p += '0';
            else if (*p < 36)
               *p += 'A'-10;
            else
               *p += 'a'-36;

            ++p;
         }
         *p = '\0';
      }


      close(fh);
   }
}


my_bool make_randstr_init(UDF_INIT *initid,
                          UDF_ARGS *args,
                          char *message)
{
   initid->maybe_null = 0;
   initid->const_item = 1;
   if (args->arg_count == 1 && args->arg_type[0] == INT_RESULT)
   {
      int val = *((int*)args->args[0]);
      if (val > 0 && val < 256 )
         return 0;
   }

   strcpy(message, "Single parameter must be integer 0<n<256.");
   return 1;
}


void make_randstr_deinit(UDF_INIT *initid)
{
}

char *make_randstr(UDF_INIT *initid,
                   UDF_ARGS *args,
                   char *result,
                   unsigned long *length,
                   char *is_null,
                   char *error)
{
   int val = *((int*)args->args[0]);
   make_random_string(result, val);
   *length = (unsigned long)val;
   *is_null = 0;

   return result;
}
