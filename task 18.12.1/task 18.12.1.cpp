// task 18.12.1.cpp 

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class User {
public:
    std::string _name;
    std::string _login;
    std::string _pass;
};

class Message {
public:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};


int main()
{    
    User tempU;
    Message tempM;
    int counter{ 0 };

    std::vector<User> users;
    std::vector<Message> messages;

    // читаем содержимое контейнера с данными пользователей
    std::ifstream readUsers("users.dat", std::ios::in);
    if (!readUsers)
    {
        std::cout << "File \"user.dat\" couldn\'t be read.\n";
    }
    else
    {
        std::string header;
        readUsers >> header;
        if (header == "users.dat")
        {
            int usersLinesSize{ 0 };
            readUsers >> usersLinesSize;
            
            std::string tempName;
            std::string tempLogin;
            std::string tempPassword;
            for (int i = 0; i < usersLinesSize; ++i)
            {
                std::getline(readUsers, tempName);
                std::getline(readUsers, tempName);
                readUsers >> tempLogin >> tempPassword;
                tempU._name = tempName;
                tempU._login = tempLogin;
                tempU._pass = tempPassword;
                users.push_back(tempU);
            }
        }
        readUsers.close();
    }

    // читаем содержимое контейнера с сообщениями
    std::ifstream readMessages("messages.dat", std::ios::in);
    if (!readMessages)
    {
        std::cout << "File \"messages.dat\" couldn\'t be read.\n";
    }
    else
    {
        std::string header;
        readMessages >> header;
        if (header == "messages.dat")
        {
            int messagesLinesSize{ 0 };
            readMessages >> messagesLinesSize;

            std::string tempText;
            std::string tempSender;
            std::string tempReceiver;
            for (int i = 0; i < messagesLinesSize; ++i)
            {
                std::getline(readMessages, tempText);
                std::getline(readMessages, tempText);
                readMessages >> tempSender >> tempReceiver;
                tempM._text = tempText;
                tempM._sender = tempSender;
                tempM._receiver = tempReceiver;
                messages.push_back(tempM);
            }
            readMessages.close();
        }
    }

    //User exampleU1{ "Ivan", "vanya12", "qwerty" };
    //users.push_back(exampleU1);
    //User exampleU2{ "Pavel Petrov", "Petrovich", "petrisfirst" };
    //users.push_back(exampleU2);
    //User exampleU3{ "Margarita", "margo%1", "!@##$%#%%#" };
    //users.push_back(exampleU3);

    // выводим нв экран содержимое контейнера с данными пользователей
    for (auto it : users)
    {
        std::cout << it._name << ' ' << it._login << ' ' << it._pass << '\n';
    }

    //Message exampleM1{ "Privet Petrovich", "vanya12", "Petrovich" };
    //messages.push_back(exampleM1);
    //Message exampleM2{ "I tebe privet", "Petrovich", "margo%1" };
    //messages.push_back(exampleM2);
    //Message exampleM3{ "How a u?", "margo%1", "vanya12" };
    //messages.push_back(exampleM3);

    // выводим нв экран содержимое контейнера с сообщениями
    for (auto it : messages)
    {
        std::cout << it._text << ' ' << it._sender << ' ' << it._receiver << '\n';
    }

    // сохраняем содержимое контейнера с данными пользователей
    std::ofstream saveUsers("users.dat", std::ios::out);
    if (!saveUsers) std::cout << "File \"user.dat\" couldn\'t be opened\n";
    saveUsers << "users.dat" << std::endl << users.size() << std::endl;
    for (auto& it : users)
    {
        saveUsers << it._name << std::endl << it._login << std::endl << it._pass << std::endl;
    }

    // сохраняем содержимое контейнера с сообщениями
    std::ofstream saveMessages("messages.dat", std::ios::out);
    if (!saveMessages) std::cout << "File \"messages.dat\" couldn\'t be opened\n";
    saveMessages << "messages.dat" << std::endl << messages.size() << std::endl;
    for (auto& it : messages)
    {
        saveMessages << it._text << std::endl << it._sender << std::endl << it._receiver << std::endl;
    }

    // устанавливаем права на чтение запись файла с данными пользователей только для владельца
    fs::permissions("users.dat",
        fs::perms::group_all | fs::perms::others_all,
        fs::perm_options::remove);

    // устанавливаем права на чтение запись файла с сообщениями только для владельца
    fs::permissions("messages.dat",
        fs::perms::group_all | fs::perms::others_all,
        fs::perm_options::remove);    

    return 0;
}