%%
% *path_obst*
obst = [[-5183,-1720];[-3948,-2387];[0,1080];[-3513,-2868];[2500,3100];[-3259,-3303];[-3323,-4296];[-3948,-3598];[-4996,-3466];[-4581,-2868]];
Ox=obst(:,1);
Oy=obst(:,2);
plot(Ox,Oy)
hold on
%Ax=[-6000;-5000];
%Ay=[-5000;-4000];
%plot(Ax,Ay)
hold on
X_RobotT=X_Robot.';
Y_RobotT=Y_Robot.';
X_Robot1T=X_Robot1.';
Y_Robot1T=Y_Robot1.';
X_Robot2T=X_Robot2.';
Y_Robot2T=Y_Robot2.';
Ax=[X_RobotT(:);X_Robot1T(:);X_Robot2T(:)];
Ay=[Y_RobotT(:);Y_Robot1T(:);Y_Robot2T(:)];
plot(Ax,Ay)
hold on