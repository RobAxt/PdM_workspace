/*
 * UserADM.c
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "UserADM.h"

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define ZERO 0

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

typedef struct
{
  uint8_t userId[MAXuSERSIZE];
  uint8_t size;
} User_t;

struct UserADM_s
{
  User_t users[MAXuSER];
};

/*----------------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static struct UserADM_s userGroup = {0};

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
bool_t APP_UserADM_AddUser(uint8_t * user, uint8_t size)
{
  bool_t storeSuccess = false;
  if(NULL != user && ZERO != size)
  {
    for(uint8_t index = 0; MAXuSER > index; index++)
    {
      if(ZERO == userGroup.users[index].size) // If user do not exists and there is an empty slot then store it
      {
        memcpy(userGroup.users[index].userId, user, size);
        userGroup.users[index].size = size;
        storeSuccess = true;
        break;
      }
      else
      {
        if(!memcmp(user, userGroup.users[index].userId, size) && size == userGroup.users[index].size) // If the user already exists
        {
          storeSuccess = true;
          break;
        }
      }
    }
  }
  return storeSuccess;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
bool_t APP_UserADM_AddDelete(uint8_t * user, uint8_t size)
{
  if(NULL != user && ZERO != size)
  {
    for(uint8_t index = 0; MAXuSER > index; index++)
    {
      if(!memcmp(user, userGroup.users[index].userId, size) && size == userGroup.users[index].size)
      {
        memset(userGroup.users[index].userId, ZERO, userGroup.users[index].size);
        userGroup.users[index].size = 0;
        return true;
      }
    }
  }
  return false;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
bool_t APP_UserADM_ValidUser(uint8_t * user, uint8_t size)
{
  if(NULL != user && ZERO != size)
  {
    for(uint8_t index = 0; MAXuSER > index; index++)
    {
      if(!memcmp(user, userGroup.users[index].userId, size) && size == userGroup.users[index].size)
      {
        return true;
      }
    }
  }
  return false;
}
/*----------------------------------------------------------------------------*/
