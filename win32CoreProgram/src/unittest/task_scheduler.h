#ifndef task_scheduler_h
#define task_scheduler_h

#include "commonpack.h"
#include "json.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>

using json = nlohmann::json;

struct Config
{
	wstring app_name = L"";
	wstring app_path = L"";
	wstring app_desc = L"";
	wstring app_param = L"";
	wstring app_start_dir = L"";
	wstring task_start_time = L"14:30";
	wstring task_start_date = L"";
	wstring task_end_date = L"";
	std::vector<pair<int, int>> start_time = {};
};

Config config;

bool DeleteTaskScheduler(int argc, char*argv[])
{
	string param = argv[1];
	if (param == "-d")
	{
		bool result = XIBAO::TaskScheduler::DeleteTaskScheduler(config.app_name);
		if (result)
		{
			std::cout << XIBAO::StringHelper::to_string(wstring(L"删除计划任务成功:")+config.app_name) << std::endl;
		}
	}
	return 0;
}


bool InitConfig()
{
	// 获取当前的所在目录
	return true;
}

bool ReadConfig()
{
	std::ifstream input("config.json");
	if (input.is_open())
	{
    json j;
    input >> j;
		string str;
		
		double version = 0.1;
		if (j.contains("version"))
		{
      version = j["version"].get<double>();
		}
		if (j.contains("app_name"))
		{
      str = j["app_name"].get<string>();
      config.app_name = XIBAO::StringHelper::to_wstring(str);
		}

		if (j.contains("app_path"))
		{
      str = j["app_path"].get<string>();
      config.app_path = XIBAO::StringHelper::to_wstring(str);
		}

		if (j.contains("app_desc"))
		{
			str = j["app_desc"].get<string>();
			config.app_desc = XIBAO::StringHelper::to_wstring(str);
		}

		if (j.contains("app_param"))
		{
			str = j["app_param"].get<string>();
			config.app_param = XIBAO::StringHelper::to_wstring(str);
		}
		
		if (j.contains("app_start_dir"))
		{
			str = j["app_start_dir"].get<string>();
			config.app_start_dir = XIBAO::StringHelper::to_wstring(str);
		}

		if (std::isEqual(0.1, version))
		{
      if (j.contains("start_time"))
      {
        str = j["start_time"].get<string>();
        config.task_start_time= XIBAO::StringHelper::to_wstring(str);
      }
		}
		else
		{
      if (j.contains("start_time"))
      {
        json o = j["start_time"];
        for (json::iterator it = o.begin(); it != o.end(); ++it) {
          int hour = (*it)["hour"].get<int>();
          int min = (*it)["min"].get<int>();
          config.start_time.push_back({ hour, min });
        }
      }
		}


		if (j.contains("start_date"))
		{
			str = j["start_date"].get<string>();
			config.task_start_date = XIBAO::StringHelper::to_wstring(str);
		}

		if (j.contains("end_date"))
		{
			str = j["end_date"].get<string>();
			config.task_end_date = XIBAO::StringHelper::to_wstring(str);
		}
	}
	else
	{
		cout << XIBAO::StringHelper::to_string(L"没有找到配置config.json文件") << endl;
		return false;
	}

	return true;
}

void print_succuss()
{
  std::cout << "------------------------------------" << std::endl;
  std::cout <<  XIBAO::StringHelper::to_string(L"任务名称:") << XIBAO::StringHelper::to_string(config.app_name) << std::endl;
  std::cout << XIBAO::StringHelper::to_string(L"app路径:") << XIBAO::StringHelper::to_string(config.app_path) << std::endl;
  std::cout << XIBAO::StringHelper::to_string(L"参数:") << XIBAO::StringHelper::to_string(config.app_param) << std::endl;
  string time_str = "";
  for (auto& time_pair : config.start_time)
  {
		time_str += std::to_string(time_pair.first) + ":" + std::to_string(time_pair.second) + "	";
  }
  std::cout << XIBAO::StringHelper::to_string(L"执行时间:") << time_str << std::endl;
  std::cout << "------------------------------------" << std::endl;
}

bool CreateTaskScheduler(const wstring &userName, const wstring &passwd)
{
	// 1、获取当前的路径，组装成绝对路径
	// 2、json格式配置
	bool result = XIBAO::TaskScheduler::DeleteTaskScheduler(config.app_name);
	if (result)
	{
		std::cout << XIBAO::StringHelper::to_string(wstring(L"删除原来的计划任务成功:")+config.app_name) << std::endl;
	}

	XIBAO::TaskScheduler task_scheduler(config.app_path,
		config.app_name,
		config.app_desc, config.app_start_dir,
		config.app_param, config.start_time, XIBAO::Win7TaskScheduler::TaskMode::LOGON_PASSWD);
	task_scheduler.SetName(userName);
	task_scheduler.SetPasswd(passwd);

	HRESULT hr= task_scheduler.CreateTaskScheduler();
	if (hr == S_OK)
	{
		std::cout << XIBAO::StringHelper::to_string(wstring(L"创建新的任务成功:")+config.app_name) << std::endl;
		return true;
	}
	else
	{
		std::cout << XIBAO::StringHelper::to_string(wstring(L"创建新的任务失败, 错误码:")+std::to_wstring(hr)) << std::endl;
		return false;
	}
	return true;
}

std::string WStringToGBK(const std::wstring& wstr) {
	int bufferSize = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* buffer = new char[bufferSize];

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buffer, bufferSize, nullptr, nullptr);

	std::string gbkStr(buffer);

	delete[] buffer;

	return gbkStr;
}

// 这种方式创建计划任务会被报毒
bool create_task(const wstring &username,const wstring &passwd)
{
	if (username.empty() || passwd.empty())
	{
		cout << XIBAO::StringHelper::to_string(L"用户名或者密码不可为空") << endl;
		return false;
	}

	wstring command_line = std::format(LR"("SCHTASKS /Create /RU {} /RP {} /SC DAILY /TN {} /TR "{} {} {}" /NP /SD {} /ED {} /ST {} /F")", username, passwd, config.app_name, config.app_path, config.app_param, config.app_start_dir,  config.task_start_date, config.task_end_date, config.task_start_time);

	int result = system(WStringToGBK(command_line).c_str());
	return result == 0;
}


#endif // task_scheduler_h