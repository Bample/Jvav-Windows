﻿/*
    Jvav Programmer Ver.1.2 Pre3 Preview
    By 30266
    Compilation time 2020-04-19 21:00
*/
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
int main()
{
    cout << "Initializing Program...\n";
    string language;
    string 命令, 类型, 输入字符串;
    string command, type, inputcharacter;
    language = "English";
    cout << "Configuring the online update service...\n";
    system("del upgrade.txt");
    system("cls");
    /*en_main*/
en_main:
    cout << "--------------------------------------------\n";
    cout << "| Jvav Program                Ver.1.2 Pre3 |\n";
    cout << "| By Dr.ZhangHaoYang                       |\n";
    cout << "| Programmer: 30266 & TZG-Official         |\n";
    cout << "| Enter'help'to get help!                  |\n";
    cout << "| Online push updates are now supported!   |\n";
    cout << "--------------------------------------------\n";
main:
    cout << "Jvav>";
    cin >> command;
    if (command == "help") {
        cout << "----Jvav help------Page(1/1)---\n";
        cout << "  help [Page]:Get help\n  leave:Exit Jvav\n  output:Output characters\n  input:Input characters\n  upgrade:Online detection of version updates\n  language:setting the program language\n  info:Jvav information\n";
        cout << "----Jvav help------Page(1/1)---\n";
        goto main;
    }
    else if (command == "leave") {
        cout << "Are you sure to leave jvav?(y/n)";
        string L;
        cin >> L;
        if (L == "y" or L == "yes") {
            return 0;
        }
        else {
            goto main;
        }
    }
    else if (command == "output") {
        cout << "Jvav>output>";
        cin >> type;
        cout << type << endl;
        goto main;
    }
    else if (command == "info") {
        cout << "Jvav Programm Ver.1.2 Pre3\nIt's just a joke, but we still make it, and the joke was first brought by Zhang Haoyang.\nThe person writing the program is 30266.\n";
        goto main;
    }
    else if (command == "input") {
        cout << "Jvav>input>";
        cin >> inputcharacter;
        goto main;
    }
    else if (command == "upgrade") {
        cout << "Jvav>upgrade>Getting a version list...\n";
        goto upgrade;
    }
    else if (command == "language") {
        cout << "Please enter the setting language(English/简体中文):";
        string language;
        cin >> language;
        if (language == "English") {
            goto main;
        }
        else if (language == "简体中文") {
            system("cls");
            goto ch;
        }
        else {
            cout << "Unknown language.\n";
            goto main;
        }
    }
    else {
        cout << "Unknown command\n";
        goto main;
    }

    /*cn_main*/
ch:
    language = "简体中文";
    cout << "--------------------------------------------\n";
    cout << "| Jvav编译器               版本：1.2  Pre3 |\n";
    cout << "| 作者：张浩洋大师                         |\n";
    cout << "| 编写者: 30266 & TZG-Official             |\n";
    cout << "| 通过输入'帮助'来获得帮助                 |\n";
    cout << "| 现已支持在线推送更新！                   |\n";
    cout << "--------------------------------------------\n";
cn_main:
    cout << "Jvav>";
    cin >> 命令;
    if (命令 == "帮助") {
        cout << "----Jvav帮助---第(1/1)页----\n";
        cout << "  帮助 [页码]:获取帮助\n  退出:退出Jvav\n  输出:输出字符\n  输入:输入字符以便调用\n  更新:在线检测版本更新\n  语言:设置Jvav的语言\n  关于:获取关于Jvav的信息\n";
        cout << "----Jvav帮助---第(1/1)页----\n";
        goto cn_main;
    }
    else if (命令 == "退出") {
        cout << "你确定要退出Jvav吗？(是/否)";
        string 退;
        cin >> 退;
        if (退 == "是" or 退 == "y" or 退 == "yes") {
            return 0;
        }
        else {
            goto cn_main;
        }
    }
    else if (命令 == "输出") {
        cout << "Jvav>输出>";
        cin >> 类型;
        cout << 类型 << endl;
        goto cn_main;
    }
    else if (命令 == "输入") {
        cout << "Jvav>输入>";
        cin >> 输入字符串;
        goto cn_main;
    }
    else if (命令 == "关于") {
        cout << "Jvav编程器，版本: 1.2 Beta3。\n这只是一个梗，但是我们依然把它变成了现实。最早是张浩洋提出的这个梗。\n该程序编写者为30266。\n";
        goto cn_main;
    }
    else if (命令 == "更新") {
        cout << "Jvav>更新>正在获取版本列表...\n";
        goto upgrade;
    }
    else if (命令 == "语言") {
        cout << "请输入您要切换的语言(简体中文/English):";
        string 语言;
        cin >> 语言;
        if (语言 == "简体中文") {
            goto cn_main;
        }
        else if (语言 == "English") {
            system("cls");
            language = "English";
            goto en_main;
        }
        else {
            cout << "未知的语言。\n";
            goto cn_main;
        }
    }
    else {
        cout << "未知的命令！\n";
        goto cn_main;
    }
    /*upgrade*/
upgrade:
    system("java -jar upgrade.jar > upgrade.txt");
    ifstream readFile("upgrade.txt");
    int ret;
    readFile >> ret; 
    readFile.close();
    if (ret == -1) {
        if (language == "English") {
            cout << "Jvav>upgrade>Error! The update failed! Because the version list cannot be obtained on the authentication server!\n";
            goto main;
        }
        else if (language == "简体中文") {
            cout << "Jvav>更新>错误！无法从认证服务器获取版本列表！\n";
            goto cn_main;
        }
    }
    else if (ret > 6) {
        if (language == "English") {
            string up;
            cout << "Jvav>upgrade>Updated versionavailable for upgrades,do you want to upgrade?(y/n)\n";
            cin >> up;
            if (up == "y") {
                system("start update.exe");
                return 0;
            }
            else {
                goto main;
            }
        }
        else if (language == "简体中文") {
            string 升;
            cout << "有更新版本可供升级，是否升级？(是/否)\n";
            cin >> 升;
            if (升 == "是") {
                system("start update.exe");
                return 0;
            }
            else {
                goto cn_main;
            }
        }
    }
    else if (ret == 6) {
        if (language == "English") {
            cout << "Congratulations! You've upgraded to the latest version!\n";
            goto main;
        }
        else {
            cout << "恭喜你！你已升级至最新版本！\n";
            goto cn_main;
        }
    }
    else {
        if (language == "English") {
            cout << "Jvav>upgrade>Error!We can't get a version list because your version is coming from a future version, so we don't support it.\n";
            goto main;
            cout << ret;
        }
        else if (language == "简体中文") {
            cout << "Jvav>更新>错误！我们无法获取版本列表，因为您的版本是来自未来的版本，故我们不提供支持。\n";
            goto cn_main;
        }
    }
}