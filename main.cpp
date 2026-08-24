#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using ipList = std::vector<std::vector<std::string>>;
ipList ip_pool;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ipList::iterator filter(int ip_part) {
    return std::lower_bound(ip_pool.begin(), ip_pool.end(), ip_part, [](std::vector<std::string> ip, int part) {
        return std::stoi(ip.at(0)) > part;
    });
}

ipList::iterator filter(std::vector<int> ip_parts) {
    return std::lower_bound(ip_pool.begin(), ip_pool.end(), ip_parts, [](std::vector<std::string> ip, std::vector<int> ip_parts) {
        if (std::stoi(ip.at(0)) != ip_parts[0]) {
            return std::stoi(ip.at(0)) > ip_parts[0];
        }
        return std::stoi(ip.at(1)) > ip_parts[1];
    });
}

ipList filter_any(int search_ip_part) {
    ipList matched_ips;
    for (auto it = ip_pool.cbegin(); it != ip_pool.cend(); ++it) {
        for (auto ip_part: *it) {
            if (std::stoi(ip_part) == search_ip_part) {
                matched_ips.push_back(*it);
                break;
            }
        }
    }

    return matched_ips;
}

void print_ip(ipList::const_iterator ip) {
    for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
    {
        if (ip_part != ip->cbegin())
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

int main()
{
    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](const std::vector<std::string> ip1, const std::vector<std::string> ip2) {
            std::vector<std::string>::const_iterator ip1_it = ip1.cbegin();
            decltype(ip1_it) ip2_it = ip2.cbegin();

            for(;ip1_it != ip1.cend(); ++ ip1_it, ++ ip2_it) {
                if (*ip1_it != *ip2_it) {
                    return std::stoi(*ip1_it) > std::stoi(*ip2_it);
                }
            }

            return true;
        });

        for(ipList::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            print_ip(ip);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        ipList::iterator it_for_part = filter(1);
        for (; it_for_part != ip_pool.end(); ++it_for_part) {
            print_ip(it_for_part);
        }

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        std::vector<int> ip_parts{46, 70};
        ipList::iterator it_for_parts = filter(ip_parts);
        for (; it_for_parts != ip_pool.end(); ++it_for_parts) {
            if (std::stoi((*it_for_parts)[0]) != ip_parts[0] || std::stoi((*it_for_parts)[1]) != ip_parts[1]) {
                break;
            }
            print_ip(it_for_parts);
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        ipList matched_ips = filter_any(46);
        for (ipList::const_iterator it = matched_ips.cbegin(); it != matched_ips.cend(); ++it) {
            print_ip(it);
        }

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
