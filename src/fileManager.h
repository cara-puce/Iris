/**
 * @file fileManager.h
 * @author M.Cherrueau & A.Carat
 * @since 05/03/2017
 * @brief all file utilities
**/
#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define DATASIZE 256
//#define STRINGSIZE 128
//#define DATAGRAMSIZE 517

typedef struct dirent dirent;

/**
 * @enum    transaction_e
 * @brief   All transaction available in iris.
 */
enum transaction_e {
  CLONE,
  CREATE,
  PULL,
  PUSH,
  REBASE,
  MKDIR,
  ACK
};

typedef enum transaction_e transaction_t;

/*
 * @struct  datagram_st
 * @brief   Define datagram
 *
 * @var transaction Transaction type
 * @var project_name Name of the project concerned
 * @var user_name Name of the user sending datagram
 * @var version Current revision
 * @var file_path Path of the file concerned
 * @var datagram_number Id of this datagram
 * @var datagram_total Number of datagram concerning the file
 * @var data_length Size of the data
 * @var data Data, what else ?
 */
struct datagram_st {
  // infos
  transaction_t transaction;
  char *project_name;
  char *user_name;
  unsigned int version;
  char *file_path;
  // data
  unsigned int datagram_number;
  unsigned int datagram_total;
  unsigned int data_length;
  char *data;
};

typedef struct datagram_st datagram_t;

/**
 * @brief Serialize a datagram.
 *
 * @param Datagram to be serialized
 *
 * @return A string representing datagram.
 */
char* serialize(datagram_t* datagram);

/**
 * @brief Unserialize a datagram.
 *
 * @param String to be unserialized
 *
 * @return A datagram.
 */
datagram_t* unserialize(char * serial);


/**
 * @brief Prepare a file for sending by cutting it into datagrams.
 * pouet/prout/file.truc
 * @param project_name Name of the project. pouet
 * @param file_path Path of the file to be cut. prout/file.truc
 * @param transaction Transaction type.
 * @param version Version of the project.
 * @param user_name Name of the user.
 * @param on_server Where the file is rebuilt : 0=client, 1=server.
 *
 * @return An array of datagrams.
 */
datagram_t **prepare_file(char* project_name, char* file_path, 
                          transaction_t transaction, unsigned int version,
                          char* user_name, int on_server);

/**
 * @brief Build a file from an array of datagrams.
 *  
 * @param project_name Name of the project.
 * @param file_path Path of the file to be re-built.
 * @param tab Array of datagrams.
 * @param on_server Where the file is rebuilt : 0=client, 1=server.
 */
void rebuild_file(char* project_name, char* file_path, unsigned int version,
                  datagram_t** tab, int on_server);

/**
* @brief Create a directory.
*
* @param dir_path Name of the directory to be created. 
*/
void create_dir(char* dir_path);

/**
* @brief Remove the content of a directory.
*
* @param dir_path Name of the directory to be renamed. 
*/
void clean_dir(char* dir_path);


#endif //__FILEMANAGER_H__