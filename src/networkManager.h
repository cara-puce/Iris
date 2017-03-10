/**
 * @file networkManager.h
 * @author M.Cherrueau & A.Carat
 * @since 05/03/2017
 * @brief all network utilities
**/
#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__


#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "fileManager.h"

#define SERVER_PORT 5000

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;


/**
 * @brief Connect a client to server.
 *
 * @param name Name of the server
 * @param port Port of the server
 *
 * @return Server socket id 
*/
int connect_to_server(char* name, unsigned int port);

/**
 * @brief Create server socket.
 *
 * @return Server socket id 
*/
int create_server_socket();

/**
 * @brief Receive data
*/
void receive_data();

/**
 * @brief Send a datagram.
 * 
 * @param socket Socket where to send
 * @param datagram Datagram to be sent
*/
void send_datagram(int socket, datagram_t * datagram);


/**
 * @brief Send a file 
 *
 * @param socket Socket where to send
 * @param project_name Name of the project. pouet
 * @param file_path Path of the file to be send. prout/file.truc
 * @param transaction Transaction type.
 * @param version Version of the project.
 * @param user_name Name of the user. 
*/
void send_file(int socket, char* project_name, char* file_path, 
               transaction_t transaction, unsigned int version,
               char* user_name);

/**
 * @brief Send a directory 
 *
 * @param project_name Name of the project. pouet
 * @param file_dir Path of the directory to be send. prout/file.truc
 * @param transaction Transaction type.
 * @param version Version of the project.
 * @param user_name Name of the user. 
*/ 
void send_dir(char* project_name, char* dir_path, 
              transaction_t transaction, unsigned int version,
              char* user_name);

#endif //__NETWORKMANAGER_H__