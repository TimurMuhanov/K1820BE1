#ifndef __K1820BE1_H__
#define __K1820BE1_H__ 1

#include "../lib/lines.h"

int K1820BE1DecodeInstruction(struct lines_t *ln);

#define K1820BE1_ERROR_CMD_NOT_FOUND            (1<<0)
#define K1820BE1_ERROR_ARG1_FOR_D_CANNOT_GET    (1<<1)
#define K1820BE1_ERROR_ARG1_FOR_D_WRONG         (1<<2)
#define K1820BE1_ERROR_ARG2_FOR_D_CANNOT_GET    (1<<3)
#define K1820BE1_ERROR_ARG2_FOR_D_WRONG         (1<<4)
#define K1820BE1_ERROR_ARG1_FOR_ALL_CANNOT_GET  (1<<5)
#define K1820BE1_ERROR_ARG1_FOR_ALL_WRONG       (1<<6)
#define K1820BE1_ERROR_JP_TRY_GO_ANOTHER_PAGE   (1<<7)
#define K1820BE1_ERROR_JP_TRY_GO_AT_END_PAGE    (1<<8)
#define K1820BE1_ERROR_JSRP_TRY_CALL_FROM_2_OR_3_PAGE   (1<<9)
#define K1820BE1_ERROR_JSRP_TRY_GO_TO_NOT_2_OR_3_PAGE   (1<<10)
#define K1820BE1_ERROR_CMD_WITH_ARG_0123        (1<<11)
#define K1820BE1_ERROR_CMD_WITH_ARG_R           (1<<12)
#define K1820BE1_ERROR_CMD_WITH_ARG_A_OR_Y      (1<<13)
#define K1820BE1_ERROR_UNEXPECTED               (1<<14)
#define K1820BE1_ERROR_RESERVE                  (1<<15)

#endif /* __K1820BE1_H__ */
