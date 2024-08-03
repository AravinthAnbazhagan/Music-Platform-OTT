#ifndef SUBSCRIPTION_H_INCLUDED
#define SUBSCRIPTION_H_INCLUDED

class Subscription {
public:
    // Member variables
    std::string name;
    double price;
    std::vector<std::string> languages;

    // Constructor
    Subscription(const std::string &name, double price, const std::vector<std::string> &languages)
        : name(name), price(price), languages(languages) {}

    // Method to display subscription details
    void display() const {
        std::cout << "Subscription Name: " << name << std::endl;
        std::cout << "Price: $" << price << std::endl;
        std::cout << "Languages: ";
        for (const auto &language : languages) {
            std::cout << language << " ";
        }
        std::cout << std::endl;
    }
};

vector<Subscription> subscriptions;

void loadSubscriptions(std::vector<Subscription> &subscriptions) {
    MYSQL* conn = mysql_init(nullptr);

    if (!conn) {
        std::cerr << "MySQL initialization failed" << std::endl;
        return;
    }

    conn = mysql_real_connect(conn, "localhost", "aravinth", "1234", "soundcloud", 0, NULL, 0);
    if (!conn) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(conn) << std::endl;
        return;
    }

    // Query to retrieve subscriptions
    std::string subscriptionQuery = "SELECT id, name, prize FROM subscriptions";
    int subscriptionQState = mysql_query(conn, subscriptionQuery.c_str());

    if (subscriptionQState != 0) {
        std::cerr << "Error executing SQL query for subscriptions: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    MYSQL_RES* subscriptionResult = mysql_store_result(conn);
    if (!subscriptionResult) {
        std::cerr << "Error retrieving result set for subscriptions: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

    MYSQL_ROW subscriptionRow;
    while ((subscriptionRow = mysql_fetch_row(subscriptionResult))) {
        int id = subscriptionRow[0] ? std::stoi(subscriptionRow[0]) : 0;
        std::string name = subscriptionRow[1] ? subscriptionRow[1] : "";
        int price = subscriptionRow[2] ? std::stoi(subscriptionRow[2]) : 0;

        // Query to retrieve languages for this subscription
        std::string languageQuery = "SELECT language FROM subscription_languages WHERE sid = " + std::to_string(id);
        int languageQState = mysql_query(conn, languageQuery.c_str());

        if (languageQState != 0) {
            std::cerr << "Error executing SQL query for languages: " << mysql_error(conn) << std::endl;
            continue;
        }

        MYSQL_RES* languageResult = mysql_store_result(conn);
        if (!languageResult) {
            std::cerr << "Error retrieving result set for languages: " << mysql_error(conn) << std::endl;
            continue;
        }

        std::vector<std::string> languages;
        MYSQL_ROW languageRow;
        while ((languageRow = mysql_fetch_row(languageResult))) {
            languages.push_back(languageRow[0] ? languageRow[0] : "");
        }

        mysql_free_result(languageResult);

        Subscription subscription(name, price, languages);
        subscriptions.push_back(subscription);
    }

    mysql_free_result(subscriptionResult);
    mysql_close(conn);
}


#endif // SUBSCRIPTION_H_INCLUDED
