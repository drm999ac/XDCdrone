clear
clc
data = zeros(1,200);
data_final = zeros(1,100);
s=serial('com20');  
s.BytesAvailableFcnMode='byte';  % 串口设置  
s.InputBufferSize=4096;  
s.OutputBufferSize=1024;  
s.BytesAvailableFcnCount=100;  
s.ReadAsyncMode='continuous'; 
s.BaudRate = 115200;
s.Terminator='CR';  
fopen(s);                  %打开串口  
Str = '55AA02040000000000000000000000AA55AAFF010000000000000000000000AA';     %字符串定义需要发送的十六进制内容
D = sscanf(Str, '%2x'); %将字符串转换成十六进制数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据

for k =1:200
out=uint8(fread(s,16,'uint8'));    
    if (all(out(1) == 85) && all(out (2) == 170) && all(out (3) == 0))  %  
        % typecast(out(4:7),'single')
        data(k) = typecast(out(8:11),'single');
        % typecast(out(12:15),'single')
    end
end
Str = '55AA02040000000000000000000000AA55AAFF000000000000000000000000AA';     %字符串定义需要发送的十六进制内容
D = sscanf(Str, '%2x'); %将字符串转换成十六进制数据
fwrite(s, D, 'uint8') %对定义的串口s发送该数据  
fwrite(s, D, 'uint8') %对定义的串口s发送该数据 
fwrite(s, D, 'uint8') %对定义的串口s发送该数据 
fwrite(s, D, 'uint8') %对定义的串口s发送该数据 
fwrite(s, D, 'uint8') %对定义的串口s发送该数据 
fwrite(s, D, 'uint8') %对定义的串口s发送该数据 
fclose(s);  
delete(s);  

for k =1:100
    data_final(k) = data(2*k);
end
% newobjs =instrfind;fclose(newobjs);