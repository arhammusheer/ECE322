/*
 * client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *num1, *num2;
    char *host, *port;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        exit(0);
    }

    num1 = argv[1];
    num2 = argv[2];

    host = "localhost";
    port = "8080";

    clientfd = Open_clientfd(host, port);

    /*
    Write your code here.
    Recommend to use the Robust I/O package.
    */

    // Build the request
    char body[MAXLINE];
    char header[MAXLINE];

    // Build the body
    sprintf(body, "<?xml version=\"1.0\"?>\r\n");
    sprintf(body + strlen(body), "<methodCall>\r\n");
    sprintf(body + strlen(body), "<methodName>sample.addmultiply</methodName>\r\n");
    sprintf(body + strlen(body), "<params>\r\n");
    sprintf(body + strlen(body), "<param><value><double>%s</double></value></param>\r\n", num1);
    sprintf(body + strlen(body), "<param><value><double>%s</double></value></param>\r\n", num2);
    sprintf(body + strlen(body), "</params>\r\n");
    sprintf(body + strlen(body), "</methodCall>\r\n");

    // Build HTTP POST Header
    sprintf(header, "POST /RPC2 HTTP/1.1\r\n");
    sprintf(header + strlen(header), "Content-Type:text/xml\r\n");
    sprintf(header + strlen(header), "User-Agent:XML-RPC.NET\r\n");
    sprintf(header + strlen(header), "Content-Length:%ld\r\n", strlen(body));
    sprintf(header + strlen(header), "Expect:100-continue\r\n");
    sprintf(header + strlen(header), "Connection:Keep-Alive\r\n");
    sprintf(header + strlen(header), "Host:localhost:8080\r\n");
    sprintf(header + strlen(header), "\r\n");

    // Append the body to the header
    sprintf(header + strlen(header), "%s", body);

    // Send the request
    Rio_writen(clientfd, header, strlen(header));

    // Read the response body
    rio_t rio;
    Rio_readinitb(&rio, clientfd);

    char values[MAXLINE];

    // Search for all values in <double> tags in the response and add them to the values string
    while (Rio_readlineb(&rio, body, MAXLINE) != 0)
    {
        if (strstr(body, "<double>") != NULL)
        {
            char *start = strstr(body, "<double>") + strlen("<double>");
            char *end = strstr(body, "</double>");
            char value[MAXLINE];
            strncpy(value, start, end - start);
            value[end - start] = '\0';
            sprintf(values + strlen(values), "%s   ", value);
        }
    }


    // Print values array
    printf("%s\n", values);
    
    Close(clientfd);
    exit(0);
}
