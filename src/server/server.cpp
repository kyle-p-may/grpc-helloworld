#include "server_impl.h"

int main(int argc, char** argv)
{
    EchoServiceImplementation::RunEchoService(std::string("localhost:50051"));
    return 0;
}