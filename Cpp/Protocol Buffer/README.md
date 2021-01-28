https://developers.google.com/protocol-buffers/docs/cpptutorial

Download Release from "https://github.com/protocolbuffers/protobuf/releases"

git clone https://github.com/protocolbuffers/protobuf.git 
release headers in google/src/google*

Run "protoc -I=./proto --cpp_out=gen proto/addressbook.proto"