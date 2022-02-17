#include <iostream>
#include <vlc.h>
#include <Windows.h>
#include <conio.h>
using namespace std;
//注意编码
std::string Unicode2Utf8(const std::wstring& strIn)
{
	std::string str;
	int length = ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), NULL, 0, NULL, NULL);
	str.resize(length + 1);
	::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), (LPSTR)str.c_str(), str.size(), NULL, NULL);
	return str;
}
//多字节=>>Unicode 再转 utf-8
int main()
{
	int argc = 1;
	const char* argv[2]{};
	argv[0] = "--ignore-config";//忽略全局配置
	libvlc_instance_t* vlc_ins = libvlc_new(argc, argv);
	std::string path = Unicode2Utf8(L"D:\\学习视频\\BaiduNetdiskDownload\\13移动打车项目\\01-java基础\\01-java基础\\3-视频\\4-java语言的值传递和引用传递_.mp4");
	libvlc_media_t* media = libvlc_media_new_path(vlc_ins, path.c_str());
	//2  media = libvlc_media_new_location(vlc_ins, "file:///D:\\VS2019code\\Test\\Debug\\测试视频.mp4");
	libvlc_media_player_t* player = libvlc_media_player_new_from_media(media);
	do
	{
		int ret = libvlc_media_player_play(player);
		if (ret == -1)
		{
			cout << "play erron" << endl;
			break;
		}
		int vol = -1;
		while (vol == -1)
		{
			Sleep(10);//只有media解析加载完成,才会有下面的参数
			vol = libvlc_audio_get_volume(player);
		}
		printf("vol is %d\r\n", vol);
		libvlc_audio_set_volume(player, 10);
		libvlc_time_t tm = libvlc_media_player_get_length(player);//ms数
		printf("%02d %02d %02d %03d\r\n", (int)tm / 3600000, (int)(tm / 60000) % 60, (int)((tm / 1000) % 60), (int)tm % 1000);
		int width = libvlc_video_get_width(player);
		int height = libvlc_video_get_height(player);
		printf("width=%d height=%d\r\n", width, height);
		while (!_kbhit())
		{
			printf("potion %f%%\r", libvlc_media_player_get_position(player) * 100.0);//可以只\r
		}
		(void)getchar();
		libvlc_media_player_pause(player);
		(void)getchar();
		libvlc_media_player_set_position(player, libvlc_media_player_get_position(player) / 2.0);
		libvlc_media_player_play(player);
		(void)getchar();
		libvlc_media_player_stop(player);
	} while (0);

	libvlc_media_player_release(player);
	libvlc_media_release(media);
	libvlc_release(vlc_ins);
}

