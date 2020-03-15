// Copyright (c) 2020 Monika Roznere, RLab @ Dartmouth College
// Copyright (c) 2020 Blue Robotics

// C++ implementation of the Blue Robotics 'Ping' binary message protocol

#ifndef PING_NODELET_PING_MESSAGE_COMMON_H
#define PING_NODELET_PING_MESSAGE_COMMON_H

#pragma once

#include "ping_nodelet/ping-message.h"

namespace ping_nodelet
{

// TODO(bluerobotics) should maybe be an enum
namespace CommonId
{
    static const uint16_t PROTOCOL_VERSION = 5;
    static const uint16_t DEVICE_INFORMATION = 4;
    static const uint16_t GENERAL_REQUEST = 6;
    static const uint16_t ACK = 1;
    static const uint16_t ASCII_TEXT = 3;
    static const uint16_t NACK = 2;
}

class common_protocol_version : public ping_message
{
public:
    explicit common_protocol_version(const ping_message& msg) : ping_message { msg } {}
    common_protocol_version(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    common_protocol_version() : ping_message { static_cast<uint16_t>(14) }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(4);  // payload size
        (uint16_t&)msgData[4] = 5;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    uint8_t version_major() const { return (uint8_t&)msgData[headerLength + 0]; }
    void set_version_major(const uint8_t version_major) { (uint8_t&)msgData[headerLength + 0] = version_major; }
    uint8_t version_minor() const { return (uint8_t&)msgData[headerLength + 1]; }
    void set_version_minor(const uint8_t version_minor) { (uint8_t&)msgData[headerLength + 1] = version_minor; }
    uint8_t version_patch() const { return (uint8_t&)msgData[headerLength + 2]; }
    void set_version_patch(const uint8_t version_patch) { (uint8_t&)msgData[headerLength + 2] = version_patch; }
    uint8_t reserved() const { return (uint8_t&)msgData[headerLength + 3]; }
    void set_reserved(const uint8_t reserved) { (uint8_t&)msgData[headerLength + 3] = reserved; }
};

class common_device_information : public ping_message
{
public:
    explicit common_device_information(const ping_message& msg) : ping_message { msg } {}
    common_device_information(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    common_device_information() : ping_message { static_cast<uint16_t>(16) }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(6);  // payload size
        (uint16_t&)msgData[4] = 4;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    uint8_t device_type() const { return (uint8_t&)msgData[headerLength + 0]; }
    void set_device_type(const uint8_t device_type) { (uint8_t&)msgData[headerLength + 0] = device_type; }
    uint8_t device_revision() const { return (uint8_t&)msgData[headerLength + 1]; }
    void set_device_revision(const uint8_t device_revision) { (uint8_t&)msgData[headerLength + 1] = device_revision; }
    uint8_t firmware_version_major() const { return (uint8_t&)msgData[headerLength + 2]; }
    void set_firmware_version_major(const uint8_t firmware_version_major)
    {
        (uint8_t&)msgData[headerLength + 2] = firmware_version_major;
    }
    uint8_t firmware_version_minor() const { return (uint8_t&)msgData[headerLength + 3]; }
    void set_firmware_version_minor(const uint8_t firmware_version_minor)
    {
        (uint8_t&)msgData[headerLength + 3] = firmware_version_minor;
    }
    uint8_t firmware_version_patch() const { return (uint8_t&)msgData[headerLength + 4]; }
    void set_firmware_version_patch(const uint8_t firmware_version_patch)
    {
        (uint8_t&)msgData[headerLength + 4] = firmware_version_patch;
    }
    uint8_t reserved() const { return (uint8_t&)msgData[headerLength + 5]; }
    void set_reserved(const uint8_t reserved) { (uint8_t&)msgData[headerLength + 5] = reserved; }
};

class common_general_request : public ping_message
{
public:
    explicit common_general_request(const ping_message& msg) : ping_message { msg } {}
    common_general_request(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    common_general_request() : ping_message { static_cast<uint16_t>(12) }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(2);  // payload size
        (uint16_t&)msgData[4] = 6;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    uint16_t requested_id() const { return (uint16_t&)msgData[headerLength + 0]; }
    void set_requested_id(const uint16_t requested_id) { (uint16_t&)msgData[headerLength + 0] = requested_id; }
};

class common_ack : public ping_message
{
public:
    explicit common_ack(const ping_message& msg) : ping_message { msg } {}
    common_ack(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    common_ack() : ping_message { static_cast<uint16_t>(12) }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(2);  // payload size
        (uint16_t&)msgData[4] = 1;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    uint16_t acked_id() const { return (uint16_t&)msgData[headerLength + 0]; }
    void set_acked_id(const uint16_t acked_id) { (uint16_t&)msgData[headerLength + 0] = acked_id; }
};

class common_ascii_text : public ping_message
{
public:
    explicit common_ascii_text(const ping_message& msg) : ping_message { msg } {}
    common_ascii_text(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    explicit common_ascii_text(uint16_t ascii_message_length) : ping_message
    {
        static_cast<uint16_t>(10 + ascii_message_length)
    }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(0 + ascii_message_length);  // payload size
        (uint16_t&)msgData[4] = 3;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    char* ascii_message() const { return reinterpret_cast<char*>(msgData+headerLength+0); }
    void set_ascii_message_at(const uint16_t i, const char data) { (char&)msgData[headerLength + 0 + i] = data; }
};

class common_nack : public ping_message
{
public:
    explicit common_nack(const ping_message& msg) : ping_message { msg } {}
    common_nack(const uint8_t* buf, const uint16_t length) : ping_message { buf, length } {}
    explicit common_nack(uint16_t nack_message_length) : ping_message
    {
        static_cast<uint16_t>(12 + nack_message_length)
    }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = static_cast<uint16_t>(2 + nack_message_length);  // payload size
        (uint16_t&)msgData[4] = 2;  // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    uint16_t nacked_id() const { return (uint16_t&)msgData[headerLength + 0]; }
    void set_nacked_id(const uint16_t nacked_id) { (uint16_t&)msgData[headerLength + 0] = nacked_id; }
    char* nack_message() const { return reinterpret_cast<char*>(msgData+headerLength+2); }
    void set_nack_message_at(const uint16_t i, const char data) { (char&)msgData[headerLength + 2 + i] = data; }
};

}  // namespace ping_nodelet

#endif  // PING_NODELET_PING_MESSAGE_COMMON_H
