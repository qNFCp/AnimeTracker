#include <bits/stdc++.h> 
#include <windows.h>

using namespace std;

//char deskpath[255]=	{"E:\\OneDrive\\����\\"};
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
		if(link.rfind("url=",0)==0){ //�������� "url="
			link.erase(0,5);//ɾ��ǰ5λ�ַ� 
			//replace(link.begin(),link.end(),'\"','\0');	//�滻"��
			link.erase(link.end()-1,link.end());//ɾ��ĩλ
			cout<<link<<'\n';
			times++;
		}
		if(link.rfind("</rss>",0)==0)//�жϽ������� 
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
			link.erase(0,5);//ɾ��ǰ5λ�ַ� 
			link.erase(link.end()-1,link.end());//ɾ��ĩλ
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
			link.erase(0,32);//ɾ��ǰ32λ�ַ� <link>http://www.miobt.com/show-
			link.erase(link.end()-12,link.end());//ɾ��ĩ12λ .html</link>
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
			cout<<"\n1.(CN) �۸̼ƻ� - Mikan Project\n2.(CN) ĩ�Մ����YԴ�� - Project AcgnX Torrent Asia\n3.(CN) MioBT�����20�������\n4.(EN) Project AcgnX Torrent Global\n";
			break;
		case 1: 
			cout<<"1.(CN) �۸̼ƻ� - Mikan Project";
		 	break;
		case 2:
			cout<<"2.(CN) ĩ�Մ����YԴ�� - Project AcgnX Torrent Asia";
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
	cout<<"AnimeTracker ������������������ ver 1.1\n\n�����������������ݾ�����ѧϰ��; This program and the generated content are for learning purposes only����\n";
	Display_library(0);
	cout<<"��ѡ����վ��(Please select site library)��\n";
	cin>>library;
	//download the RSS document	
	cout<<"\nע����������Ļ��м��ʹ�üӺŸ�������\nʷ��ķ+��ӣ+1080+mp4+big5\nNote: If there are multiple parameters, you can use + to link them. e.g.\nNeko+movie+japan+anime\n\n";
	cout<<"�������(Key in the parameters):";
	cin>>key;
	
	//���뼰д������ 
	freopen("temp.txt", "w", stdout);
	int times=0; //��ʼ�������� �����жϽ���Ƿ�Ϊ��
	
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

	//�Ͽ��ļ����� 
	fclose(stdin);
	fclose(stdout);
	
	dell("temp.xml");
	//�������Ϊ��ʱ ɾ�����ļ� �����´�����־
	if(times==0){
		dell("temp.txt");
		freopen("AnimeTracker_ErrorLog.txt", "w", stdout);
		cout<<"No resources found for \""<<key<<"\" in library \"";
		Display_library(library);
		cout<<"\"";
		return 0;
	}
	
	//�޸��ļ���
	char rename[255]={0};
	sprintf(rename,"ren \"temp.txt\" %s.txt\"",key);
	cout<<rename; 
	system(rename);	
	return 0;
} 
