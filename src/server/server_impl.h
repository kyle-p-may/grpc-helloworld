#ifndef SERVER_SERVER_IMPL_H
#define SERVER_SERVER_IMPL_H

#include <string>
#include <iostream>

#include <grpc++/grpc++.h>
#include "echo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using echo::Echo;
using echo::EchoRequest;
using echo::EchoReply;

class EchoServiceImplementation final : public Echo::Service {
    Status EchoMessage(ServerContext* context, const EchoRequest* request, EchoReply* reply) override
    {
        std::string message = request->message();
        std::cout << "client sent us: " << message << std::endl;

        reply->set_message(message);

        return Status::OK;
    }

  public:
    static void RunEchoService(const std::string& address)
    {
        EchoServiceImplementation service;
        ServerBuilder builder;

        builder.AddListeningPort(address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on port: " << address << std::endl;

        server->Wait();
    }
};

#endif