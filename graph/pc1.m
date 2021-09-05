fileID = fopen('datasp.txt','r');
x = cell2mat(textscan(fileID,'%f'));

dense1 = fopen('time1.txt','r');
d1 = cell2mat(textscan(dense1,'%d'));

sparse1 = fopen('time4.txt','r');
sp1 = cell2mat(textscan(sparse1,'%d'));
sp1 = rescale(sp1,min(d1),max(d1));

dense2 = fopen('time2.txt','r');
d2 = cell2mat(textscan(dense2,'%d'));

sparse2 = fopen('time5.txt','r');
sp2 = cell2mat(textscan(sparse2,'%d'));
sp2 = rescale(sp1,min(d2),max(d2));

dense3 = fopen('time3.txt','r');
d3 = cell2mat(textscan(dense3,'%d'));

sparse3 = fopen('time6.txt','r');
sp3 = cell2mat(textscan(sparse3,'%d'));
sp3 = rescale(sp3,min(d3),max(d3));

figure(1);
plot(x,sp1,'-b');
hold on
str1 = {'red line->dense','blue line->sparse'};
text(0.8,825,str1);
xlabel('sparsity');
ylabel('time(\mus)');
title('m=30 n=40 p=50');
plot(x,d1,'-r');
hold off


figure(2);
plot(x,sp2,'-b');
hold on
str2 = {'red line->dense','blue line->sparse'};
text(0.6,55,str2);
xlabel('sparsity');
ylabel('time(ms)');
title('m=100 n=150 p=200');
plot(x,d2,'-r');
hold off

figure(3);
plot(x,sp3,'-b');
hold on
str3 = {'red line->dense','blue line->sparse'};
text(0.8,300,str3);
xlabel('sparsity');
ylabel('time(ms)');
title('m=300 n=300 p=300');
plot(x,d3,'-r');
hold off