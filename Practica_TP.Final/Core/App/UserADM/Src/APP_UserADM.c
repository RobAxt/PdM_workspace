/*
 * UserADM.c
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include <APP_UserADM.h>

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
  * @brief  Adds an user to the system
  * @param  uint8_t * user: uid of the readed tag
  * @param  uint8_t size: size of the UId readed
  * @retval bool_t return true if the user could be added
  */
bool_t APP_UserADM_AddUser(uint8_t * user, uint8_t size)
{
  bool_t storeSuccess = false;
  if(NULL != user && ZERO != size)
  {
    for(uint8_t index = 0; MAXuSER > index; index++)
    {
      // If user do not exists and there is an empty slot then store it
      if(ZERO == userGroup.users[index].size)
      {
        memcpy(userGroup.users[index].userId, user, size);
        userGroup.users[index].size = size;
        storeSuccess = true;
        break;
      }
      else
      { // If the user already exists do nothing and enjoy the easy success
        if(!memcmp(user, userGroup.users[index].userId, size) && size == userGroup.users[index].size)
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
  * @brief  Delete an user from the system
  * @param  uint8_t * user: uid of the readed tag
  * @param  uint8_t size: size of the UId readed
  * @retval bool_t return true if the user could be deleted
  */
bool_t APP_UserADM_DeleteUser(uint8_t * user, uint8_t size)
{
  if(NULL != user && ZERO != size)
  {
    for(uint8_t index = 0; MAXuSER > index; index++)
    {
      // Find the user and delete
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
  * @brief  Validates if the user exists or not
  * @param  uint8_t * user: uid of the readed tag
  * @param  uint8_t size: size of the UId readed
  * @retval bool_t indicates if the user is valid or not
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
