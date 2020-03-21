local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_LuaProtobuf", BaseLayer)

--[[
-- To Gen addressbook.pb
-- protoc -o addressbook.pb ./addressbook.proto  --proto_path ./
-- soruce code of addressbook.proto

// See README.txt for information and build instructions.
//
// Note: START and END tags are used in comments to define sections used in
// tutorials.  They are not part of the syntax for Protocol Buffers.
//
// To get an in-depth walkthrough of this file and the related examples, see:
// https://developers.google.com/protocol-buffers/docs/tutorials

// [START declaration]
syntax = "proto3";
package tutorial;

// [END declaration]

// [START java_declaration]
option java_package = "com.example.tutorial";
option java_outer_classname = "AddressBookProtos";
// [END java_declaration]

// [START csharp_declaration]
option csharp_namespace = "Google.Protobuf.Examples.AddressBook";
// [END csharp_declaration]

// [START messages]
message Person {
  string name = 1;
  int32 id = 2;  // Unique ID number for this person.
  string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    string number = 1;
    PhoneType type = 2;
  }

  repeated PhoneNumber phones = 4;
}

// Our address book file is just one of these.
message AddressBook {
  repeated Person people = 1;
}
// [END messages]

]]--


local pb = require "luapb" -- different name from pbc

function TestCase:ctor()
	self.super.ctor(self)

	self:setNodeEventEnabled(true)
	-- tips
	local label = display.newTTFLabel({
		text = "Encode & Decode addressbook.pb",
		size = 25,
		color = cc.c3b(255, 255, 255),
	})
	label:align(display.CENTER, display.cx, display.cy + 200)
	self:addChild(label)

	-- test code
	assert(pb.loadfile(cc.FileUtils:getInstance():fullPathForFilename("addressbook.pb")))

	local person = {
		name = "Alice",
		id = 12345,
		phones = {
			{ number = "1301234567" },
			{ number = "87654321", type = "WORK" },
		}
	}

	-- 序列化成二进制数据
	local data = assert(pb.encode("tutorial.Person", person))
	print("pb.encode data length:" .. #data)
	-- 从二进制数据解析出实际消息
	local msg = assert(pb.decode("tutorial.Person", data))
	-- 打印消息内容（使用了serpent开源库）
	dump(msg, "pb.decode")
end

return TestCase
