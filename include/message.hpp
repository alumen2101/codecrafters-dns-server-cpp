#ifndef MESSAGE_H
#define MESSAGE_H


#include <netinet/in.h>

#include <vector>


using ByteArray = std::vector<unsigned char>;


class Message {
private:

    ByteArray header_;

public:
    Message() {
        header_.reserve(12);

        append_uint16(header_, 1234);

        unsigned char opcode = 0;
        header_.push_back((opcode << 3) | 0x80);

        unsigned char rcode = 0;
        header_.push_back((rcode << 4) | 0x00);

        uint16_t qdcount = 0;
        append_uint16(header_, qdcount);

        uint16_t ancount = 0;
        append_uint16(header_, ancount);

        uint16_t nscount = 0;
        append_uint16(header_, nscount);

        uint16_t arcount = 0;
        append_uint16(header_, arcount);
    }

    [[nodiscard]] const unsigned char *getArray() const { return header_.data(); }
    [[nodiscard]] size_t size() const { return header_.size(); }

private:

    void append_uint16(ByteArray& arr, uint16_t value) {
        arr.push_back(static_cast<unsigned char>((value >> 8) & 0xFF));
        arr.push_back(static_cast<unsigned char>(value & 0xFF));
    }


};


#endif //MESSAGE_H
