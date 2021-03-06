#ifdef WIN32
#include <direct.h>
#endif
/*
    Jvav Programmer Ver.02w05c Snapshot
    By 30266
    Compilation time 2020-04-16 21:00
    ----------------------------------
    Jvav Programmer Ver.03w00c Snapshot
    By Amiriox
    Compilation time 2020-05-15 15:24
    ----------------------------------
    Jvav Programmer Ver.2 Release
    By Amiriox
    Compilation time 2020-06-02 12:56
    ----------------------------------
    Jvav Programmer Ver.2.1
    By Amiriox
    Compilation time 2020-06-02 20:00
    ----------------------------------
    Jvav Programmer Ver.2.2 Snapshot
    By Amiriox
    Compilation time 2020-06-03 09:30
    ----------------------------------
    Jvav Programmer Ver.2.2.1
    By Amiriox
    Compilation time 2020-06-04 09:53
     ----------------------------------
    Jvav Programmer Ver.2.3
    By Amiriox
    Compilation time 2020-06-10 10:00
    -----------------------------------
    Jvav Programmer Ver.2.3 ReBuild
    By yuzijiangorz
    Compilation time 2020-6-10 14:39
    -----------------------------------
    Jvav Programmer Ver.2.3 fix-ReBuild
    By Amiriox
    Compilation time 2020-6-15 18:31
*/
#include <io.h>
#ifdef WIN32
#include <windows.h>
#endif  // WIN32

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "JVMplus.h"
using namespace std;
void executeMainLoop(int status=1);
void compileFile(string fileName,int status=0);
void makePackage(string sourceFile,string outFile,int status=0);

const double curVersion = 2.3;
void   getLibrary();
map<string, int> settingCommandMap;
string command;


void windowsInit() {
#ifdef WIN32

    system("chcp 65001");
    if (_access("wget.exe", 0) == -1) {
        printf("fatal Error: Lost wget.exe ");
        return;
    }
    if (_access("upgrade.exe", 0) == -1) {
        printf("fatal Error: Lost upgrade.exe");
    }
    system("rd /s /q C:\\Jvav");
    system("rd /s /q C:\\Jvav\\lib");
    system("rd /s /q C:\\Jvav\\resource");

    system("mkdir C:\\Jvav");
    system("mkdir C:\\Jvav\\lib");
    system("mkdir C:\\Jvav\\resource");

    Sleep(2000);
    system(
        "wget http://47.105.108.192/Jvav/identifier.res -O "
        "C:\\Jvav\\resource\\identifier.res");
#endif  // WINDOWS
}

void all_init() {
#ifdef WIN32
    windowsInit();
    getLibrary();
#endif

#ifdef linux
    cout << "your os is linux." << endl;
    // TODO Linux version
#endif
}
void getLibrary(){
    printf("getting lib...\n");
    system("rd /s /q C:\\Jvav\\lib");
    system("mkdir C:\\Jvav\\lib");
    system("wget http://47.105.108.192/Jvav/lib.7z");
    system("7z.exe x lib.7z -oC:\\Jvav\\lib");
    CHAR c[MAX_PATH];
    DWORD result = GetCurrentDirectoryA(MAX_PATH, c);
    std::string direy(c);
    std::string delCmd = "rd /s /q "+direy+"\\lib.7z";
    system(delCmd.c_str());
}
/*
    * void checkupdate
    Args: {
        * status: 0为例行检查, 1为主动检查
    }
    DO: check the update
    Author: yuzijiangorz & Amiriox(Rebuild)
*/
void checkUpgrade(int status=0) {
    system("chcp 65001");
    system("wget http://47.105.108.192/Jvav/newest.txt");
    FILE *fp = fopen("newest.txt", "w");
    double ver;
    fscanf(fp, "Ver %.2f", &ver);
    fclose(fp);
    system("del newest.txt");
    if (ver == curVersion) {
        if (status)
            printf("The newest version.\n");
        else
            return;
    }
    if (ver > curVersion) {
        cout << "Jvav is old version. Upgrade?(y/n): ";
        char isUp;
        cin >> isUp;
        if (isUp == 'y') {
            system("update.exe");
        } else {
            cout << "You gave up updating. Execute `jcp update` to update."
                 << endl;
        }
    }
}
void init_() {
#ifdef WIN32
    if (_access("wget.exe", 0) == -1) {
        printf("fatal Error: Lost wget.exe\n ");
        return;
    }
    if (_access("upgrade.exe", 0) == -1) {
        printf("fatal Error: Lost upgrade.exe\n");
        return;
    }
#endif
    // settings map init;
    settingCommandMap["-strict=false"] = 1;
    settingCommandMap["-strict=true"] = 2;
    settingCommandMap["-std"] = 3;
}

void setConsoleColor(string color) {
#ifdef WIN32
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);

    if (color == "red")
        SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_INTENSITY);
    if (color == "blue")
        SetConsoleTextAttribute(hd, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (color == "yellow")
        SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_GREEN);
#endif  // WIN32
}
void backToDefautColor(void) {
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        hd, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
bool tmpstrict = false;
int tmpversion = 11;
void processChangeSettings(string set_c) {
    switch (settingCommandMap[set_c]) {
        case 1: {
            tmpstrict = false;
            setConsoleColor("blue");
            cout << "Strict Mode already been closed." << endl;
            backToDefautColor();
            break;
        }
        case 2: {
            tmpstrict = true;
            setConsoleColor("blue");
            cout << "Strict Mode already been opened.";
            backToDefautColor();
            break;
        }
        case 3: {
            cout << "Input 11 or 14 or 17 for jvav standard version: ";
            bool outputWarning = bool(tmpversion);
            cin >> tmpversion;
            setConsoleColor("blue");
            cout << "The standard has been set to " << tmpversion << endl;
            if (outputWarning) {
                setConsoleColor("yellow");
                cout << "Warning: Before you set it up, the standard version "
                        "is not the default"
                     << endl;
            }
            backToDefautColor();
            break;
        }
        default: {
            cout << "Unknown Setting Options.\n" << endl;
            break;
        }
    }
};
void printPreInfo() {
    cout << "---------------------------------------------\n";
    cout << "| Jvav Program               Ver.3.1        |\n";
    cout << "| By Dr.ZhangHaoYang    Programmer Amiriox  |\n";
    cout << "| Enter 'help' to get help!                 |\n";
    cout << "| Online push updates are now supported!    |\n";
    cout << "| Compile vav source file are now supported!|\n";
    cout << "---------------------------------------------\n";
	executeMainLoop();
}
void printInfo(){
	cout<< "Jvav Programm Ver.3.1 Pre1\nIt's just a joke, but we still "
                   "make it, and the joke was first brought by Zhang "
                   "Haoyang.\nThis version supports running away from "
                   "jdk.\nThe person writing the program is Amiriox and yuzijiangorz.\n";
    executeMainLoop();
}
void printHelpPage() {
    cout << "----Jvav help------Page(1/1)---\n";
    cout << "  help [page]:Get help\n  compile [filename]:compile "
            "source code\n"
            "leave:Exit Jvav\n  output:Output \n"
            "jvins [source code filename] [execute filename]: make a "
            "package for your source code\n"
            "characters\n  input:Input characters\n  upgrade:Online "
            "detection of version updates\n  language:setting the "
            "program "
            "language\n  info:Jvav information\n";
    cout << "----Jvav help------Page(1/1)---\n";
	executeMainLoop();
}
void compileFile(string fileName,int status) {
    JvavVirtualMachine jvav_compiler(fileName);
    jvav_compiler.setStrictMode(tmpstrict);
    jvav_compiler.setStandardVersion(tmpversion);
    STATUS_VALUE compile_result = jvav_compiler.compile();
    if (compile_result == STATUS_SUCCESS) {
        cout << "\nCompile successfully.\n";
    } else if (compile_result == STATUS_NO_GPP) {
        cout << "\nCompiler error or there is no g++ compiler "
                "environment!\n";
    } else if (compile_result == STATUS_NO_IDEN) {
        cout << "\nThe identifier file is missing, please check if the "
                "identity.res file is in good condition.\n";
        cout << "installing identifier library for your device.\n";
        all_init();
        cout << "Your device has already had identifier library.\n";
        cout << "Please re-execute the compile command.\n";
    } else if (compile_result == STATUS_NO_INPUT) {
        cout << "\nThere are no such files in the directory.\n";
    } else {
        cout << "\nUnknown Error.\n";
    }
	if(status==0)
	executeMainLoop();
}
void topLevelSettings() {
	setConsoleColor("yellow");
	cout << "Warning: ";
	setConsoleColor("blue");
	cout << "You are changing your settings.\n";
	backToDefautColor();
	cout << "Please enter the Settings you want to change,\nenter quit "
            "to quit: \n";
	string tmp;
    std::cin >> tmp;
    while (tmp != "quit") {
	    processChangeSettings(tmp);
        std::cin >> tmp;
    }
    executeMainLoop();
}
void makePackage(string sourceFile,string outFile,int status){
            cin >> sourceFile;
            cin >> outFile;
            JvavVirtualMachine jvav_compiler(sourceFile);
            jvav_compiler.setStrictMode(tmpstrict);
            jvav_compiler.setStandardVersion(tmpversion);
            jvav_compiler.setMakePackageOptions(outFile);
            STATUS_VALUE compile_result = jvav_compiler.compile();
            if (compile_result == STATUS_SUCCESS) {
                cout << "\nCompile successfully.\n";
            } else if (compile_result == STATUS_NO_GPP) {
                cout << "\nCompiler error or there is no g++ compiler "
                        "environment!\n";
            } else if (compile_result == STATUS_NO_IDEN) {
                cout << "\nThe identifier file is missing, please check if the "
                        "identity.res file is in good condition.\n";
                cout << "installing identifier library for your device.\n";
                all_init();
                cout << "Your device has already had identifier library.\n";
                cout << "Please re-execute the compile command.\n";
            } else if (compile_result == STATUS_NO_INPUT) {
                cout << "\nThere are no such files in the directory.\n";
            } else {
                cout << "\nUnknown Error.\n";
            }
	if(status==0)
            executeMainLoop();
}
void executeMainLoop(int status) {
	
    if (status != 1) return;
    cout << "Jvav>";
    std::cin >> command;
    if (command == "help") {
        printHelpPage();
    } else if (command == "compile" || command == "cl") {
        string file;
        std::cin >> file;
        compileFile(file);
    } else if (command == "settings" || command == "set") {
        topLevelSettings();
    } else if (command == "jvins" || command == "jvi") {
        string s_file;
		string o_file;
		makePackage(s_file,o_file);
    } else if (command == "info") {
		printInfo();
    } else if (command == "exit" || command == "EXIT" || command == "quit") {
        return;
    } else {
        cout << "Unknown command\n";
        executeMainLoop();
    }
}
int main(int argc, char **argv) {
    init_();
    if (argc == 1) {
        cout << "Initializing program...\n";
        ////cout << "Configuring the online update service...\n";
        ///system("del upgrade.txt");
		//cout << "checking upgrade...\n";
		//checkUpgrade();
		#ifdef WIN32
			Sleep(9000);
		#endif
        system("cls");
        printPreInfo();
		executeMainLoop();
    }else{
		string type = argv[1];
		if(type=="-c") {
			if(argc<3){
				setConsoleColor("red");
				cout << "fatal error: no input files." <<endl;
				backToDefautColor();
			}
			string file=argv[2];
			compileFile(file,1);
		}
		if(type=="-o") {
			if(argc<4){
				setConsoleColor("red");
				cout << "fatal error: missing argument." << endl;
			}
			string s_file = argv[2];
			string o_file = argv[3];
			makePackage(s_file,o_file,1);
		}
		if(type=="-u")
			checkUpgrade(1);
        if(type=="init"){
            all_init();
        }
	}
}

//* --------------Rubbish Code
// // // void windowsInit(){
// // //     std::string folderPath = "C:\\Jvav";
// // //     if (0 != access(folderPath.c_str(), 0)) {
// // //         int result = mkdir(folderPath.c_str());
// // //         if(result!=0) cout << endl << "Failed to create folder
// // \'C:\\Jvav\'"<<endl;
// // //     }
// // //     folderPath = "C:\\Jvav\\lib";
// // //     if (0 != access(folderPath.c_str(), 0)) {
// // //         int result = mkdir(folderPath.c_str());
// // //         if(result!=0) cout << endl << "Failed to create folder
// // \'C:\\Jvav\\lib\'"<<endl;
// // //     }
// // //     folderPath = "C:\\Jvav\\resource";
// // //     if (0 != access(folderPath.c_str(), 0)) {
// // //         int result = mkdir(folderPath.c_str());
// // //         if(result!=0) cout << endl << "Failed to create folder
// // \'C:\\Jvav\\resource\'"<<endl;
// // //     }
// // //     system("powershell (new-object System.Net.WebClient).DownloadFile(
// // 'https://cdn.yuzijiangorz.xyz/identifier.res','C:\\Jvav\\resource\\identifier.res')");

// // // }
    //    // else if(cmd=="env"){
    //     //     changeEnvironmentVar();
    //     //     string a = viewEnvironmentVar("test");
    //     //     cout << a << endl;
    //     //     system("P1177");
    //     //     system("pause");
    //     // }
 // // main:
    // //     cout << "Jvav>";
    // //     cin >> command;
    // //     if (command == "help") {
    // //         cout << "----Jvav help------Page(1/1)---\n";
    // //         cout << "  help [page]:Get help\n  compile [filename]:compile "
    // //                 "source code\n"
    // //                 "leave:Exit Jvav\n  output:Output \n"
    // //                 "jvins [source code filename] [execute filename]: make a "
    // //                 "package for your source code\n"
    // //                 "characters\n  input:Input characters\n  upgrade:Online "
    // //                 "detection of version updates\n  language:setting the "
    // //                 "program "
    // //                 "language\n  info:Jvav information\n";
    // //         cout << "----Jvav help------Page(1/1)---\n";
    // //         goto main;
    // //     } else if (command == "compile" || command == "cl") {
    // //         string fileName;
    // //         cin >> fileName;
    // //         JvavVirtualMachine jvav_compiler(fileName);
    // //         jvav_compiler.setStrictMode(tmpstrict);
    // //         jvav_compiler.setStandardVersion(tmpversion);
    // //         STATUS_VALUE compile_result = jvav_compiler.compile();
    // //         if (compile_result == STATUS_SUCCESS) {
    // //             cout << "\nCompile successfully.\n";
    // //         } else if (compile_result == STATUS_NO_GPP) {
    // //             cout << "\nCompiler error or there is no g++ compiler "
    // //                     "environment!\n";
    // //         } else if (compile_result == STATUS_NO_IDEN) {
    // //             cout << "\nThe identifier file is missing, please check if the "
    // //                     "identity.res file is in good condition.\n";
    // //             cout << "installing identifier library for your device.\n";
    // //             all_init();
    // //             cout << "Your device has already had identifier library.\n";
    // //             cout << "Please re-execute the compile command.\n";
    // //         } else if (compile_result == STATUS_NO_INPUT) {
    // //             cout << "\nThere are no such files in the directory.\n";
    // //         } else {
    // //             cout << "\nUnknown Error.\n";
    // //         }
    // //         goto main;
    // //     } else if (command == "settings" || command == "set") {
    // //         HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    // //         SetConsoleTextAttribute(hd, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    // //         cout << "tips: ";
    // //         hd = GetStdHandle(STD_OUTPUT_HANDLE);
    // //         // SetConsoleColor( FOREGROUND_RED, BACKGROUND_BLUE |
    // //         // FOREGROUND_GREEN );
    // //         SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_GREEN);
    // //         cout << "Warning: ";
    // //         hd = GetStdHandle(STD_OUTPUT_HANDLE);
    // //         SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_INTENSITY);
    // //         cout << "You are changing your settings\n";
    // //         SetConsoleTextAttribute(
    // //             hd, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // //         cout << "Please enter the Settings you want to change,\nenter quit "
    // //                 "to quit: \n";
    // //         string tmp;
    // //         cin >> tmp;
    // //         while (tmp != "quit") {
    // //             processChangeSettings(tmp);
    // //             cin >> tmp;
    // //         }
    // //         goto main;
    // //     } else if (command == "jvins" || command == "jvi") {
    // //         string fileName;
    // //         cin >> fileName;
    // //         string _oname;
    // //         cin >> _oname;
    // //         JvavVirtualMachine jvav_compiler(fileName);
    // //         jvav_compiler.setStrictMode(tmpstrict);
    // //         jvav_compiler.setStandardVersion(tmpversion);
    // //         jvav_compiler.setMakePackageOptions(_oname);
    // //         STATUS_VALUE compile_result = jvav_compiler.compile();
    // //         if (compile_result == STATUS_SUCCESS) {
    // //             cout << "\nCompile successfully.\n";
    // //         } else if (compile_result == STATUS_NO_GPP) {
    // //             cout << "\nCompiler error or there is no g++ compiler "
    // //                     "environment!\n";
    // //         } else if (compile_result == STATUS_NO_IDEN) {
    // //             cout << "\nThe identifier file is missing, please check if the "
    // //                     "identity.res file is in good condition.\n";
    // //             cout << "installing identifier library for your device.\n";
    // //             all_init();
    // //             cout << "Your device has already had identifier library.\n";
    // //             cout << "Please re-execute the compile command.\n";
    // //         } else if (compile_result == STATUS_NO_INPUT) {
    // //             cout << "\nThere are no such files in the directory.\n";
    // //         } else {
    // //             cout << "\nUnknown Error.\n";
    // //         }
    // //         goto main;
    // //     } else if (command == "leave") {
    // //         cout << "Are you sure to leave jvav?(y/n)";
    // //         string L;
    // //         cin >> L;
    // //         if (L == "y") {
    // //             return 0;
    // //         } else {
    // //             goto main;
    // //         }
    // //     } else if (command == "output") {
    // //         cout << "Jvav>output>";
    // //         cin >> type;
    // //         cout << type << endl;
    // //         goto main;
    // //     } else if (command == "info") {
    // //         cout
    // //             << "Jvav Programm Ver.1.2 Pre1\nIt's just a joke, but we still "
    // //                "make it, and the joke was first brought by Zhang "
    // //                "Haoyang.\nThis version supports running away from "
    // //                "jdk.\nThe "
    // //                "person writing the program is 30266 and Amiriox.\n";
    // //         goto main;
    // //     } else if (command == "input") {
    // //         cout << "Jvav>input>";
    // //         cin >> inputcharacter;
    // //         goto main;
    // //     } else if (command == "upgrade") {
    // //         cout << "Jvav>upgrade>Sorry, we are developing this feature.\n";
    // //         goto main;
    // //     } else if (command == "exit" || command == "EXIT") {
    // //         return 0;
    // //     } else {
    // //         cout << "Unknown command\n";
    // //         goto main;
    // //     }

    // // } else {
    // //     string cmd = argv[1];
    // //     if (cmd == "-c") {
    // //         string fileName = argv[2];
    // //         JvavVirtualMachine jvav_compiler(fileName);
    // //         jvav_compiler.setStrictMode(false);
    // //         jvav_compiler.setStandardVersion(11);
    // //         STATUS_VALUE compile_result = jvav_compiler.compile();
    // //         if (compile_result == STATUS_SUCCESS) {
    // //             cout << "\nCompile successfully.\n";
    // //         } else if (compile_result == STATUS_NO_GPP) {
    // //             cout << "\nCompiler error or there is no g++ compiler "
    // //                     "environment!\n";
    // //         } else if (compile_result == STATUS_NO_IDEN) {
    // //             cout << "\nThe identifier file is missing, please check if the "
    // //                     "identity.res file is in good condition.\n";
    // //             cout << "installing identifier library for your device.\n";
    // //             all_init();
    // //             cout << "Your device has already had identifier library.\n";
    // //             cout << "Please re-execute the compile command.\n";
    // //         } else if (compile_result == STATUS_NO_INPUT) {
    // //             cout << "\nThere are no such files in the directory.\n";
    // //         } else {
    // //             cout << "\nUnknown Error.\n";
    // //         }
    // //     } else if (cmd == "-o") {
    // //         string fileName = argv[2];
    // //         string _oname = argv[3];
    // //         JvavVirtualMachine jvav_compiler(fileName);
    // //         jvav_compiler.setStrictMode(false);
    // //         jvav_compiler.setStandardVersion(11);
    // //         jvav_compiler.setMakePackageOptions(_oname);
    // //         STATUS_VALUE compile_result = jvav_compiler.compile();
    // //         if (compile_result == STATUS_SUCCESS) {
    // //             cout << "\nCompile successfully.\n";
    // //         } else if (compile_result == STATUS_NO_GPP) {
    // //             cout << "\nCompiler error or there is no g++ compiler "
    // //                     "environment!\n";
    // //         } else if (compile_result == STATUS_NO_IDEN) {
    // //             cout << "\nThe identifier file is missing, please check if the "
    // //                     "identity.res file is in good condition.\n";
    // //             cout << "installing identifier library for your device.\n";
    // //             all_init();
    // //             cout << "Your device has already had identifier library.\n";
    // //             cout << "Please re-execute the compile command.\n";
    // //         } else if (compile_result == STATUS_NO_INPUT) {
    // //             cout << "\nThere are no such files in the directory.\n";
    // //         } else {
    // //             cout << "\nUnknown Error.\n";
    // //         }
    // //     } else if (cmd == "init") {
    // //         all_init();
    // //         cout << "JCP has been initialized." << endl;
    // //         cout << "Updating Jvav Library...\n\n\n" << endl;
    // //         system("update.exe");
    // //         cout << "\n\n\nAll initialized." << endl;
    // //     } else if (cmd == "update") {
    // //         system("update.exe");
    // //         all_init();
    // //     }

//----
// //     /*cn_main*/
// // ch:
// //     language = "锟斤拷锟斤拷锟斤拷锟斤拷";
// //     cout << "--------------------------------------------\n";
// //     cout << "| Jvav锟斤拷锟斤拷锟斤拷             锟芥本锟斤拷2.1
// //     预锟斤拷锟斤拷0     |\n"; cout << "|
// //     锟斤拷锟竭ｏ拷锟脚猴拷锟斤拷锟绞?           锟斤拷写锟竭ｏ拷30266
// //     |\n"; cout << "|
// //     Jvav锟斤拷锟斤拷平台锟斤拷Jvav锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷:
// //     Amiriox     |\n"; cout << "|
// //     JCP/Jvins锟斤拷锟斤拷锟斤拷模式锟斤拷锟窖撅拷锟斤拷锟斤拷使锟斤拷!
// //     |\n"; cout << "|
// //     通锟斤拷锟斤拷锟斤拷'锟斤拷锟斤拷'锟斤拷锟斤拷冒锟斤拷锟? |\n";
// //     cout << "| 锟斤拷锟斤拷支锟斤拷锟斤拷锟斤拷锟斤拷锟酵革拷锟铰ｏ拷
// //     |\n"; cout << "| 锟斤拷锟斤拷支锟街憋拷锟斤拷Jvav源锟侥硷拷!
// //     |\n"; cout << "--------------------------------------------\n";
// // cn_main:
// //     cout << "Jvav>";
// //     cin >> cn_command;
// //     if (cn_command == "锟斤拷锟斤拷") {
// //         cout << "----Jvav锟斤拷锟斤拷---锟斤拷(1/1)页----\n";
// //         cout << "  锟斤拷锟斤拷 [页锟斤拷]:锟斤拷取锟斤拷锟斤拷\n
// //         锟剿筹拷:锟剿筹拷Jvav\n  "
// //                 "锟斤拷锟斤拷
// //                 [锟侥硷拷锟斤拷]:锟斤拷锟斤拷源锟侥硷拷\n
// //                 锟斤拷锟斤拷 [源锟侥硷拷锟斤拷] "
// //                 "[锟斤拷执锟斤拷锟侥硷拷锟斤拷]:
// //                 锟斤拷锟缴匡拷执锟斤拷锟侥硷拷\n"
// //                 "锟斤拷锟?:锟斤拷锟斤拷址锟絓n  "
// //                 "锟斤拷锟斤拷:锟斤拷锟斤拷锟街凤拷锟皆憋拷锟斤拷锟絓n
// //                 锟斤拷锟斤拷:锟斤拷锟竭硷拷锟芥本锟斤拷锟斤拷\n  "
// //                 "cn_lang:锟斤拷锟斤拷Jvav锟斤拷锟斤拷锟斤拷\n
// //                 锟斤拷锟斤拷:锟斤拷取锟斤拷锟斤拷Jvav锟斤拷锟斤拷息\n";
// //         cout << "----Jvav锟斤拷锟斤拷---锟斤拷(1/1)页----\n";
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         // TODO :
// //
// 锟斤拷锟斤拷水平,锟剿达拷锟睫凤拷锟斤拷锟斤拷太锟斤拷锟斤拷募锟?(300锟斤拷锟斤拷锟斤拷)
// //         string fileName;
// //         cin >> fileName;
// //         JvavVirtualMachine jvav_compiler(fileName);
// //         jvav_compiler.setStrictMode(tmpstrict);
// //         jvav_compiler.setStandardVersion(tmpversion);
// //         STATUS_VALUE compile_result = jvav_compiler.compile();
// //         if (compile_result == STATUS_SUCCESS) {
// //             cout << "\n锟斤拷锟斤拷晒锟?.\n";
// //         } else if (compile_result == STATUS_NO_GPP) {
// //             cout <<
// //
// "\n锟斤拷锟斤拷失锟斤拷,锟斤拷锟斤拷锟斤拷锟斤法锟斤拷锟斤拷锟矫伙拷锟絞++锟斤拷锟斤拷.\n";
// //         } else if (compile_result == STATUS_NO_IDEN) {
// //             cout <<
// // "\n锟斤拷识锟斤拷锟侥硷拷锟斤拷失,锟斤拷锟斤拷\"identifier.res\"\n";
// //         } else if (compile_result == STATUS_NO_INPUT) {
// //             cout << "\n目录锟斤拷没锟斤拷指锟斤拷锟斤拷源锟侥硷拷\n";
// //         } else {
// //             cout << "\n未知锟斤拷锟斤拷.\n";
// //         }
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
// //         SetConsoleTextAttribute(hd, FOREGROUND_BLUE |
// //         FOREGROUND_INTENSITY); cout << "锟斤拷示: "; hd =
// //         GetStdHandle(STD_OUTPUT_HANDLE);
// //         // SetConsoleColor( FOREGROUND_RED, BACKGROUND_BLUE |
// //         // FOREGROUND_GREEN );
// //         SetConsoleTextAttribute(hd, FOREGROUND_RED |
// //         FOREGROUND_GREEN); cout << "锟斤拷锟斤拷: "; hd =
// //         GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hd,
// //         FOREGROUND_RED | FOREGROUND_INTENSITY); cout <<
// //         "锟斤拷锟斤拷锟节革拷锟斤拷锟斤拷锟斤拷\n";
// //         SetConsoleTextAttribute(
// //             hd, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
// //         cout <<
// //         "锟斤拷锟斤拷锟斤拷锟斤拷要锟斤拷锟侥碉拷锟斤拷锟斤拷选锟斤拷,\n
// //         锟斤拷锟斤拷\"锟剿筹拷\"锟皆憋拷锟剿筹拷: \n"; string tmp;
// //         cin >> tmp;
// //         while (tmp != "锟剿筹拷") {
// //             processChangeSettings(tmp);
// //             cin >> tmp;
// //         }
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         string fileName;
// //         cin >> fileName;
// //         string _oname;
// //         cin >> _oname;
// //         JvavVirtualMachine jvav_compiler(fileName);
// //         jvav_compiler.setStrictMode(tmpstrict);
// //         jvav_compiler.setStandardVersion(tmpversion);
// //         jvav_compiler.setMakePackageOptions(_oname);
// //         STATUS_VALUE compile_result = jvav_compiler.compile();
// //         if (compile_result == STATUS_SUCCESS) {
// //             cout << "\nCompile successfully.\n";
// //         } else if (compile_result == STATUS_NO_GPP) {
// //             cout << "\nCompiler error or there is no g++ compiler "
// //                     "environment!\n";
// //         } else if (compile_result == STATUS_NO_IDEN) {
// //             cout << "\nThe identifier file is missing, please check
// //             if the "
// //                     "identity.res file is in good condition.\n";
// //         } else if (compile_result == STATUS_NO_INPUT) {
// //             cout << "\nThere are no such files in the directory.\n";
// //         } else {
// //             cout << "\nUnknown Error.\n";
// //         }
// //         goto cn_main;
// //     } else if (cn_command == "锟剿筹拷") {
// //         cout << "锟斤拷确锟斤拷要锟剿筹拷Jvav锟斤拷(锟斤拷/锟斤拷)";
// //         string cn_back;
// //         cin >> cn_back;
// //         if (cn_back == "锟斤拷") {
// //             return 0;
// //         } else {
// //             goto cn_main;
// //         }
// //     } else if (cn_command == "锟斤拷锟?") {
// //         cout << "Jvav>锟斤拷锟?>";
// //         cin >> cn_type;
// //         cout << cn_type << endl;
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         cout << "Jvav>锟斤拷锟斤拷>";
// //         cin >> cn_input_char;
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         cout <<
// //         "Jvav锟斤拷锟斤拷锟?,锟斤拷Jvav锟斤拷锟斤拷平台锟斤拷锟芥本为2."
// //
// "2预锟斤拷锟斤拷1锟斤拷\n锟斤拷只锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷然锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞碉拷锟斤拷锟斤拷锟?"
// //                 "锟斤拷锟斤拷"
// //
// "锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷\n锟矫版本支锟斤拷锟斤拷锟斤拷jdk锟斤拷锟斤拷锟叫★拷锟斤拷锟斤拷要g++"
// //                 "锟斤拷锟斤拷锟斤拷\n锟矫筹拷锟斤拷锟叫达拷锟轿?3"
// //                 "0266锟斤拷Amiriox锟斤拷\n";
// //         goto cn_main;
// //     } else if (cn_command == "锟斤拷锟斤拷") {
// //         cout <<
// //
// "Jvav>锟斤拷锟斤拷>锟皆诧拷锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷诳锟斤拷锟斤拷锟?.\n";
// //         goto cn_main;
// //     } else if (cn_command == "cn_lang") {
// //         cout <<
// //
// "锟斤拷锟斤拷锟斤拷锟斤拷要锟叫伙拷锟斤拷锟斤拷锟斤拷(锟斤拷锟斤拷锟斤拷锟斤拷/English):";
// //         string cn_lang;
// //         cin >> cn_lang;
// //         if (cn_lang == "锟斤拷锟斤拷锟斤拷锟斤拷") {
// //             goto cn_main;
// //         } else if (cn_lang == "English") {
// //             system("cls");
// //             language = "English";
// //             goto en_main;
// //         } else {
// //             cout << "未知锟斤拷锟斤拷锟皆★拷\n";
// //             goto cn_main;
// //         }
// //     } else {
// //         cout << "未知锟斤拷锟斤拷锟筋！\n";
// //         goto cn_main;
// //     }
// /*
// ! upgrade
// ! can not run!
// */
// // upgrade:
// //     system("java -jar upgrade.jar > upgrade.txt");
// //     ifstream readFile("upgrade.txt");
// //     int ret;
// //     readFile >> ret;
// //     readFile.close();
// //     if (ret == -1) {
// //         if (language == "English") {
// //             cout << "Jvav>upgrade>Error! The update failed! Because
// //             the "
// //                     "version "
// //                     "list cannot be obtained on the authentication "
// //                     "server!\n";
// //             goto main;
// //         } else if (language == "锟斤拷锟斤拷锟斤拷锟斤拷") {
// //             cout <<
// //
// "Jvav>锟斤拷锟斤拷>锟斤拷锟斤拷锟睫凤拷锟斤拷锟斤拷证锟斤拷锟斤拷锟斤拷锟斤拷取锟芥本锟叫憋拷锟斤拷\n";
// //             goto cn_main;
// //         }
// //     } else if (ret > 6) {
// //         if (language == "English") {
// //             cout << "Jvav>upgrade>Updated versionavailable for
// //             upgrades, "
// //                     "please "
// //                     "go to "
// //                     "https://30266-official.github.io/updates/Jvav.zip
// //                     " "download!\n";
// //             goto main;
// //         } else if (language == "锟斤拷锟斤拷锟斤拷锟斤拷") {
// //             cout <<
// // "锟叫革拷锟铰版本锟缴癸拷锟斤拷锟斤拷锟斤拷锟斤拷前锟斤拷https://"
// // "30266-official.github.io/updates/Jvav.zip锟斤拷锟截ｏ拷\n";
// //             goto cn_main;
// //         }
// //     } else if (ret == 6) {
// //         if (language == "English") {
// //             cout << "Congratulations! You've upgraded to the latest "
// //                     "version!\n";
// //             goto main;
// //         } else {
// //             cout <<
// // "锟斤拷喜锟姐！锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰版本锟斤拷\n";
// //             goto cn_main;
// //         }
// //     } else {
// //         if (language == "English") {
// //             cout
// //                 << "Jvav>upgrade>Error!We can't get a version list
// //                 because "
// //                    "your version is coming from a future version, so
// //                    we " "don't " "support it.\n";
// //             goto main;
// //             cout << ret;
// //         } else if (language == "锟斤拷锟斤拷锟斤拷锟斤拷") {
// //             cout << "Jvav>锟斤拷锟斤拷>"
// //
// "锟斤拷锟斤拷锟斤拷锟斤拷锟睫凤拷锟斤拷取锟芥本锟叫憋拷锟斤拷锟斤拷为锟斤拷锟侥版本锟斤拷锟斤拷锟斤拷未锟斤拷锟侥帮拷"
// //                     "锟斤拷锟斤拷"
// //                     "锟斤拷锟斤拷锟角诧拷锟结供支锟街★拷\n";
// //             goto cn_main;
// //         }
// //     }
