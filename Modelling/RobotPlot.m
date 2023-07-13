%%
% *RobotPlot*
X_Robot=out.X_Robot;
X_Robot1=out.X_Robot1;
X_Robot2=out.X_Robot2;
Y_Robot=out.Y_Robot;
Y_Robot1=out.Y_Robot1;
Y_Robot2=out.Y_Robot2;
a=size(X1);
for n=1:a(1)
plot(X_Robot(n,:),Y_Robot(n,:))
hold on
end
b=size(X2);
for n=1:b(1)
plot(X_Robot1(n,:),Y_Robot1(n,:))
hold on
end
c=size(X3);
for n=1:c(1)
plot(X_Robot2(n,:),Y_Robot2(n,:))
hold on
end
axis equal
