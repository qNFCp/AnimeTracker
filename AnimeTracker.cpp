#include <bits/stdc++.h> 
#include <windows.h>

using namespace std;

//char deskpath[255]=	{"E:\\OneDrive\\桌面\\"};
//char deskpath[255]={"\%userprofile\%\\desktop\\"};
char del[255];
char rss[3253],key[610];
int library=1;

void dell(string temp){ //delete
	char delpath[255];
	temp.copy(delpath,temp.length(),0);
	*(delpath+temp.length())='\0';
	sprintf(del,"del \"%s\"",delpath);
	system(del);
	//sprintf(del,"del \"%sfile_name\"",deskpath);	
	//system(del);
}

void rssdownload(string temp){
	char tem[255];
	temp.copy(tem,temp.length(),0);	
	sprintf(rss,"powershell (new-object System.Net.WebClient).DownloadFile( \'%s%s\',\'temp.xml\')",tem,key);	
	//sprintf(rss,"powershell (new-object System.Net.WebClient).DownloadFile( \'https://mikanani.me/RSS/Search?searchstr=%s\',\'%stemp.xml\')",key,deskpath);	
	system(rss);
}

int mikan(){
	freopen("temp.xml", "r", stdin);
	string link;
	int times=0;
	while(cin>>link){
		if(link.rfind("url=",0)==0){ //搜索内容 "url="
			link.erase(0,5);//删除前5位字符 
			//replace(link.begin(),link.end(),'\"','\0');	//替换"号
			link.erase(link.end()-1,link.end());//删除末位
			cout<<link<<'\n';
			times++;
		}
		if(link.rfind("</rss>",0)==0)//判断结束读入 
			break;	
	}	
	return times;
}

int acgnx(){
	freopen("temp.xml", "r", stdin);
	string link;
	int times=0;
	while(cin>>link){
		if(link.rfind("url=",0)==0){
			link.erase(0,5);//删除前5位字符 
			link.erase(link.end()-1,link.end());//删除末位
			cout<<link<<'\n';
			times++;
		}
		if(link.rfind("</rss>",0)==0)
			break;
	}
	return times;
}

int miobt(){
	//download
	sprintf(rss,"powershell (new-object System.Net.WebClient).DownloadFile( \'https://www.miobt.com/rss-%s.xml\',\'temp.xml\')",key);
	system(rss);
	//link to file
	freopen("temp.xml", "r", stdin);
	string link;
	int times=0;
	while(cin>>link){
		if(link.rfind("<link>http://www.miobt.com/show",0)==0){
			//<link>http://www.miobt.com/show-f6e92dd78b479edde8149478e146f8e3aa364820.html</link>
			link.erase(0,32);//删除前32位字符 <link>http://www.miobt.com/show-
			link.erase(link.end()-12,link.end());//删除末12位 .html</link>
			cout<<"magnet:?xt=urn:btih:"<<link<<"&tr=http://open.acgtracker.com:1096/announce\n";
			times++;
		}
		if(link.rfind("</rss>",0)==0)
			break;
	}
	return times;
}

void Display_library(int a){
	switch(a){
		case 0:
			cout<<"\n1.(CN) 蜜柑计划 - Mikan Project\n2.(CN) 末日動漫資源庫 - Project AcgnX Torrent Asia\n3.(CN) MioBT（最多20条结果）\n4.(EN) Project AcgnX Torrent Global\n";
			break;
		case 1: 
			cout<<"1.(CN) 蜜柑计划 - Mikan Project";
		 	break;
		case 2:
			cout<<"2.(CN) 末日動漫資源庫 - Project AcgnX Torrent Asia";
			break;
		case 3:
			cout<<"3.(CN) MioBT";
			break;
		case 4:
			cout<<"4.(EN) Project AcgnX Torrent Global";
			break;
	}
}

int main(){
	for(int i=0;i<40;i++) cout<<" "; 
	cout<<"AnimeTracker 番剧种子批量导出器 ver 1.1\n\n！！本程序及生成内容均仅供学习用途 This program and the generated content are for learning purposes only！！\n";
	Display_library(0);
	cout<<"请选择网站库(Please select site library)：\n";
	cin>>library;
	//download the RSS document	
	cout<<"\n注：多个参数的话中间可使用加号隔开，例\n史莱姆+幻樱+1080+mp4+big5\nNote: If there are multiple parameters, you can use + to link them. e.g.\nNeko+movie+japan+anime\n\n";
	cout<<"键入参数(Key in the parameters):";
	cin>>key;
	
	//读入及写入连接 
	freopen("temp.txt", "w", stdout);
	int times=0; //初始化计数器 用于判断结果是否为空
	
	if(library==1){
		rssdownload("https://mikanani.me/RSS/Search?searchstr=");		
		times=mikan();
	}	
	if(library==2){
		rssdownload("https://share.acgnx.se/rss.xml?keyword=");
		times=acgnx();
	}
	if(library==3){
		times=miobt();
	}
	if(library==4){
		rssdownload("https://www.acgnx.se/rss.xml?keyword=");
		times=acgnx();
	}

	//断开文件连接 
	fclose(stdin);
	fclose(stdout);
	
	dell("temp.xml");
	//搜索结果为空时 删除空文件 并留下错误日志
	if(times==0){
		dell("temp.txt");
		freopen("AnimeTracker_ErrorLog.txt", "w", stdout);
		cout<<"No resources found for \""<<key<<"\" in library \"";
		Display_library(library);
		cout<<"\"";
		return 0;
	}
	
	//修改文件名
	char rename[255]={0};
	sprintf(rename,"ren \"temp.txt\" %s.txt\"",key);
	cout<<rename; 
	system(rename);	
	return 0;
} 
