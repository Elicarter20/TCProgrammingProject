Code breaks after reading a 0000 or 01303030 but process the zero however.
FIXED!

check_file format isnt finished exactly....only checks type and format for first file


Application Protocol
Types of messages
There is only one type of message, a single byte
Syntax and semantics of each message type
Format of messages
Meaning of each field in the format
Value range of each field
Rules of sending messages




































Basing test cases off 3 fields... need to write a script!!!!!!!!
    IF = input file     T = translation type  RF = target file
    For all tests:     server is open at port 8060
            client connects to localhost 127.0.0.1 at port 8060
    
Case
Input
Expected Output
Result
Client input file does not exist.
IF = *nonexistent file*
T = “0”
RF = “r.txt”
Server: Sends Rejection
Client: Format Error
Server: Sends Rejection
Client: Format Error
Client input file is empty.
IF = *empty file*
T = “0”
RF = “r.txt”
Server: Sends Rejection
Client: Format Error
Server: Sends Rejection
Client: Format Error
Client provides incorrect translation type format.
IF = *correct file*
T = “00”,”a”,”4”
RF = “r.txt”
Server: Sends Rejection
Client: Format Error
Server: Sends Rejection
Client: Format Error
File is only type 0, with 































































































































