#pragma once

#include <string>

inline std::string constructNodeName(const std::string &ns, const std::string &name) {
    std::string node_name;
    if (ns.empty()) {
        return name;
    } else {
        if (ns.front() != '/') { // 确保命名空间以单斜杠开头
            node_name = "/" + ns;
        } else {
            node_name = ns;
        }
        if (!node_name.empty() && node_name.back() != '/') { // 添加服务名，确保中间只有一个斜杠
            node_name += "/";
        }
        node_name += name;
    }
    return node_name;
}
