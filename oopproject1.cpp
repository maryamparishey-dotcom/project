#include<iostream>
#include<string>
#include<cctype>

using namespace std;

class Cipher {

private:
    string ciphername;

public:

    Cipher(string n) : ciphername(n) {}

    virtual string encrypt(string message) = 0;
    virtual string decrypt(string message) = 0;

    string getName() {
        return ciphername;
    }

    virtual ~Cipher() {}
};

class Caesarcipher : public Cipher {

private:

    int shift;

    char shiftchar(char ch, int shift) {

        if (ch >= 'A' && ch <= 'Z') {
            return ((ch - 'A' + shift + 26) % 26) + 'A';
        }

        else if (ch >= 'a' && ch <= 'z') {
            return ((ch - 'a' + shift + 26) % 26) + 'a';
        }

        return ch;
    }

public:

    Caesarcipher() : Cipher("Caesar Cipher") {
        shift = 3;
    }

    string encrypt(string message) {

        for (int i = 0; i < message.length(); i++) {
            message[i] = shiftchar(message[i], shift);
        }

        return message;
    }

    string decrypt(string message) {

        for (int i = 0; i < message.length(); i++) {
            message[i] = shiftchar(message[i], -shift);
        }

        return message;
    }
};

class Atbashcipher : public Cipher {

private:

    char transformchar(char ch) {

        if (ch >= 'A' && ch <= 'Z') {
            return 'Z' - (ch - 'A');
        }

        else if (ch >= 'a' && ch <= 'z') {
            return 'z' - (ch - 'a');
        }

        return ch;
    }

public:

    Atbashcipher() : Cipher("Atbash Cipher") {}

    string encrypt(string message) {

        for (int i = 0; i < message.length(); i++) {
            message[i] = transformchar(message[i]);
        }

        return message;
    }

    string decrypt(string message) {

        for (int i = 0; i < message.length(); i++) {
            message[i] = transformchar(message[i]);
        }

        return message;
    }
};

class Message {

private:

    string sender;
    string receiver;
    string encryptedmessage;
    string cipherused;

public:

    Message() {

        sender = "";
        receiver = "";
        encryptedmessage = "";
        cipherused = "";
    }

    void setSender(string s) {
        sender = s;
    }

    void setReceiver(string r) {
        receiver = r;
    }

    void setEncryptedmessage(string message) {
        encryptedmessage = message;
    }

    void setCipherUsed(string cipher) {
        cipherused = cipher;
    }

    string getSender() {
        return sender;
    }

    string getReceiver() {
        return receiver;
    }

    string getEncryptedmessage() {
        return encryptedmessage;
    }

    string getCipherUsed() {
        return cipherused;
    }
};

class chatsystem {

private:

    Message messages[200];

    int messagecount;

    string password;

    Atbashcipher atbash;
    Caesarcipher caesar;

    Cipher* currentcipher;

    string contact[3];

    string decryptMessage(string encrypted,
                          string cipherType) {

        if (cipherType == "Caesar Cipher") {
            return caesar.decrypt(encrypted);
        }

        else if (cipherType == "Atbash Cipher") {
            return atbash.decrypt(encrypted);
        }

        return "Unknown cipher";
    }

public:

    chatsystem() {

        messagecount = 0;

        currentcipher = &caesar;

        password = "cipher123";

        contact[0] = "Ali";
        contact[1] = "Amna";
        contact[2] = "Zainab";
    }

    void SendMessage(string sendername,
                     string receiver,
                     string message) {

        bool validSender = false;
        bool validReceiver = false;

        for (int i = 0; i < 3; i++) {

            if (contact[i] == sendername) {
                validSender = true;
            }

            if (contact[i] == receiver) {
                validReceiver = true;
            }
        }
        
        if (validSender && validReceiver) {

            Message newMsg;

            newMsg.setSender(sendername);
            newMsg.setReceiver(receiver);

            string encryptmessage =
                currentcipher->encrypt(message);

            newMsg.setEncryptedmessage(encryptmessage);

            newMsg.setCipherUsed(currentcipher->getName());

            messages[messagecount] = newMsg;

            messagecount++;

            cout << "\nMessage sent successfully."
                 << endl;

            cout << "The message has been encrypted."
                 << endl;
        }

        else {

            cout << "\nInvalid sender or receiver name."
                 << endl;

            cout << "Allowed contacts are: "
                 << "Ali, Amna, and Zainab."
                 << endl;
        }
    }

    void selectCipher(int choice) {

        if (choice == 1) {

            currentcipher = &caesar;

            cout << "\nCaesar cipher selected."
                 << endl;
        }

        else if (choice == 2) {

            currentcipher = &atbash;

            cout << "\nAtbash cipher selected."
                 << endl;
        }

        else {

            cout << "\nInvalid cipher choice."
                 << endl;
        }
    }

    void viewallmessages() {

        if (messagecount == 0) {

            cout << "\nNo messages available."
                 << endl;

            return;
        }

        cout << "\nEncrypted messages"
             << endl;

        for (int i = 0; i < messagecount; i++) {

            cout << "\nMessage "
                 << i + 1
                 << endl;

            cout << "Sender   : "
                 << messages[i].getSender()
                 << endl;

            cout << "Receiver : "
                 << messages[i].getReceiver()
                 << endl;

            cout << "Message  : "
                 << messages[i].getEncryptedmessage()
                 << endl;

            cout << "Cipher   : "
                 << messages[i].getCipherUsed()
                 << endl;
        }

        string pass;

        cout << "\nEnter password to decrypt messages: ";
        cin >> pass;

        if (password == pass) {

            cout << "\nChat history"
                 << endl;

            for (int i = 0; i < messagecount; i++) {

                string decrypted =
                    decryptMessage(
                        messages[i].getEncryptedmessage(),
                        messages[i].getCipherUsed()
                    );

                cout << "\nMessage "
                     << i + 1
                     << endl;

                cout << "Sender   : "
                     << messages[i].getSender()
                     << endl;

                cout << "Receiver : "
                     << messages[i].getReceiver()
                     << endl;

                cout << "Message  : "
                     << decrypted
                     << endl;
            }
        }

        else {

            cout << "\nIncorrect password."
                 << endl;
        }
    }

    void viewsinglemessage(int index) {

        if (index < 0 || index >= messagecount) {

            cout << "\nInvalid message number."
                 << endl;

            return;
        }

        string pass;

        cout << "\nEnter password: ";
        cin >> pass;

        if (password == pass) {

            string decrypted =
                decryptMessage(
                    messages[index].getEncryptedmessage(),
                    messages[index].getCipherUsed()
                );

            cout << "\nSender   : "
                 << messages[index].getSender()
                 << endl;

            cout << "Receiver : "
                 << messages[index].getReceiver()
                 << endl;

            cout << "Message  : "
                 << decrypted
                 << endl;
        }

        else {

            cout << "\nIncorrect password."
                 << endl;
        }
    }

    void viewEncryptedOnly() {

        if (messagecount == 0) {

            cout << "\nNo encrypted messages found."
                 << endl;

            return;
        }

        cout << "\nEncrypted messages"
             << endl;

        for (int i = 0; i < messagecount; i++) {

            cout << "\nMessage "
                 << i + 1
                 << endl;

            cout << "Sender   : "
                 << messages[i].getSender()
                 << endl;

            cout << "Receiver : "
                 << messages[i].getReceiver()
                 << endl;

            cout << "Message  : "
                 << messages[i].getEncryptedmessage()
                 << endl;

            cout << "Cipher   : "
                 << messages[i].getCipherUsed()
                 << endl;
        }
    }

    int getMessageCount() {
        return messagecount;
    }

    string getCurrentCipherName() {
        return currentcipher->getName();
    }
};

int main() {

    chatsystem chat;

    string userName;
    string rec;

    int choice;
cout << "\n";
cout << "+--------------------------------------+\n";
cout << "¦          CIPHER CHAT SYSTEM          ¦\n";
cout << "+--------------------------------------+\n";
 

    cout << "Secure and Confidential communication using encryption"
         << endl;
    cout << "+-----------------------------------------------------+\n";
    cout << "\nDefault password: cipher123"
         << endl;
    cout<< "Allowed contacts are : Ali, Amna, and Zainab."<<endl;
    cout << "Current cipher: "
         << chat.getCurrentCipherName()
         << endl;

    do {

        cout << "\nMain Menu"
             << endl;

        cout << "1. Send message"
             << endl;

        cout << "2. View all messages"
             << endl;

        cout << "3. View a single message"
             << endl;

        cout << "4. View encrypted messages"
             << endl;

        cout << "5. Change cipher"
             << endl;

        cout << "6. Exit"
             << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1) {

            string message;

            cout << "\nEnter sender name: ";
            getline(cin, userName);

            cout << "Enter receiver name: ";
            getline(cin, rec);

            cout << "Enter your message: ";
            getline(cin, message);

            chat.SendMessage(userName,
                             rec,
                             message);
        }

        else if (choice == 2) {

            chat.viewallmessages();
        }

        else if (choice == 3) {

            if (chat.getMessageCount() == 0) {

                cout << "\nNo messages available."
                     << endl;
            }

            else {

                int index;

                cout << "\nEnter message number between 1 and "
                     << chat.getMessageCount()
                     << ": ";

                cin >> index;

                chat.viewsinglemessage(index - 1);
            }
        }

        else if (choice == 4) {

            chat.viewEncryptedOnly();
        }

        else if (choice == 5) {

            int cipherChoice;

            cout << "\nSelect a cipher"
                 << endl;

            cout << "1. Caesar cipher"
                 << endl;

            cout << "2. Atbash cipher"
                 << endl;

            cout << "Enter your choice: ";
            cin >> cipherChoice;

            chat.selectCipher(cipherChoice);
        }

        else if (choice == 6) {

            cout << "\nThank you for using "
                 << "Cipher Chat System."
                 << endl;
        }

        else {

            cout << "\nInvalid menu choice."
                 << endl;
        }

    } while (choice != 6);

    return 0;
}
