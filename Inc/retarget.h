// All credit to Carmine Noviello for this code
// https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f030R8/system/include/retarget/retarget.h

#ifndef _RETARGET_H__
#define _RETARGET_H__

//#include "stm32g4xx_it.h"
#include <sys/stat.h>
#include "usart.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void RetargetInit(UART_HandleTypeDef *huart);
    int _isatty(int fd);
    int _write(int fd, char *ptr, int len);
    int _close(int fd);
    int _lseek(int fd, int ptr, int dir);
    int _read(int fd, char *ptr, int len);
    int _fstat(int fd, struct stat *st);

#ifdef __cplusplus
} // extern “C”
#endif

#endif //#ifndef _RETARGET_H__