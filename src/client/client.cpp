#include <string>
#include <iostream>
#include <memory>

#include <grpc++/grpc++.h>
#include "echo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc:: Status;

using echo::Echo;
using echo::EchoReply;
using echo::EchoRequest;

class EchoClient {
    public:
        EchoClient(std::shared_ptr<Channel> channel)
        : stub_(Echo::NewStub(channel))
        { }

        std::string sendRequest(const std::string& message) {
            EchoRequest request;
            EchoReply reply;
            ClientContext context;

            request.set_message(message);
            Status status = stub_->EchoMessage(&context, request, &reply);

            if (status.ok()) {
                return reply.message();
            } else {
                return "ERROR: server didn't return result";
            }
        }

    private:
        std::unique_ptr<Echo::Stub> stub_;
};

int main(int argc, char** argv)
{
    std::string address("localhost:50051");
    EchoClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

    std::string message = "Hello gRPC";

    auto response = client.sendRequest(message);

    std::cout << "we sent: " << message << std::endl << "we recv'd: " << response << std::endl;

    return 0;
}