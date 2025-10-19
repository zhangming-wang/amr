#pragma once
#include <QDateTime>
#include <QString>
inline QString get_cmd_string_prefix() {
    return " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";
}

static constexpr const char *OK_STYLESHEET = "color:green;font-size:20px;"; // background-color:green;
static constexpr const char *ERROR_STYLESHEET = "color:red;font-size:20px;";