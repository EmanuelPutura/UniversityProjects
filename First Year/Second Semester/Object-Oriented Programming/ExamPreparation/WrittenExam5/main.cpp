#include <iostream>
#include <string>
#include <ctime>
#include <crtdbg.h>

class Channel {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~Channel() = default;
};

class Telephone : public Channel {
private:
    std::string number;
public:
    Telephone(const std::string& number) : number(number) {
    }

    void send(const std::string& message) override {
        int random = rand() % 10;
        if (random % 2 == 0)
            throw std::runtime_error("The line is busy!");
        std::cout << "dialing " << number << "\n";
    }
};

class Fax : public Telephone {
public:
    Fax(const std::string& number) : Telephone(number) {
    }

    ~Fax() = default;

    void send(const std::string& message) override {
        Telephone::send(message);
        std::cout << "sending fax, message: '" << message << "'\n";
    }
};

class SMS : public Telephone {
public:
    SMS(const std::string& number) : Telephone(number) {
    }

    ~SMS() = default;

    void send(const std::string& message) override {
        Telephone::send(message);
        std::cout << "sending sms, message: '" << message << "'\n";
    }
};

class Failover : public Channel {
private:
    Channel& channel1;
    Channel& channel2;
public:
    Failover(Channel& channel1, Channel& channel2) : channel1(channel1), channel2(channel2) {
    }

    ~Failover() = default;

    void send(const std::string& message) override {
        try {
            channel1.send(message);
            return;
        }
        catch (std::runtime_error& error1) {
            std::cout << error1.what() << '\n';
        }

        channel2.send(message);
    }
};

class Contact {
private:
    Channel& channel1;
    Channel& channel2;
    Channel& channel3;
public:
    Contact(Channel& channel1, Channel& channel2, Channel& channel3)
            : channel1(channel1), channel2(channel2), channel3(channel3) {
    }

    void sendAlarm(const std::string& message) const {
        while (true) {
            try {
                channel1.send(message);
                break;
            }
            catch (std::runtime_error& error) {
                std::cout << "First line is busy: " << error.what() << '\n';
            }

            try {
                channel2.send(message);
                break;
            }
            catch (std::runtime_error& error) {
                std::cout << "Second line is busy: " << error.what() << '\n';
            }

            try {
                channel2.send(message);
                break;
            }
            catch (std::runtime_error& error) {
                std::cout << "All channel are busy: " << error.what() << '\n';
            }
        }
    }
};

void function() {
    srand(time(NULL));

    Telephone telephone {"0754458595"};
    Fax fax {"0754458595"};
    SMS sms {"0754458595"};

    Failover failover1 {fax, sms};
    Failover failover2 {telephone, failover1};

    Contact contact {telephone, failover1, failover2};
    contact.sendAlarm("Message from the future: You did great at the OOP exam, young padawan! :)");
}

int main() {
    function();

    int r = _CrtDumpMemoryLeaks();
    printf("Memory Leaks: %d\n", r);

    return 0;
}
