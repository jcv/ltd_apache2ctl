/*
A tiny utility to let non-super users restart apache2 on Linux. 
The makefile sets suid permission magic that makes this work.
Copyright 2015 Josiah Johnston. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_ARG_LEN 16

int main(int argc, char *argv[]) {
  int apache_return_val;
  if( argc > 1 ) {
    if( strncmp( argv[1], "configtest", MAX_ARG_LEN ) == 0 ) {
      apache_return_val = system( "/usr/sbin/apache2ctl configtest" );
      return apache_return_val;
    } else
    if( strncmp( argv[1], "restart", MAX_ARG_LEN ) == 0 ) {
      apache_return_val = system( "/usr/sbin/apache2ctl configtest" );
      if( apache_return_val == 0 ) {
        apache_return_val = system( "/usr/sbin/apache2ctl restart" );
        if( apache_return_val == 0 ) printf("Restart successful\n");
        else printf("Restart was problematic. Please check error messages, fix the problem and try again.\n");
        return apache_return_val;
      } else {
        printf("\n\nThe configuration files have an error. Refusing to restart apache until the errors are corrected.\n\n");
      }
      return apache_return_val;
    } else
    if( strncmp( argv[1], "reload", MAX_ARG_LEN ) == 0 ) {
      apache_return_val = system( "/usr/sbin/apache2ctl configtest" );
      if( apache_return_val == 0 ) {
        apache_return_val = system( "/usr/sbin/apache2ctl -k graceful" );
        if( apache_return_val == 0 ) printf("Reload successful\n");
        else printf("Restart was problematic. Please check error messages, fix the problem and try again.\n");
        return apache_return_val;
      } else {
        printf("\n\nThe configuration files have an error. Refusing to restart apache until the errors are corrected.\n\n");      
      }
      return apache_return_val;
    }
  } 
  printf( "Usage: %s configtest|restart|reload\n", argv[0]);
  return 0;
}
