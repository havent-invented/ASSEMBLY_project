hold off
x= linspace(-10,10,401);


y1= 2.5-x+x;
plot(x, y1 , '-', 'LineWidth', 1);
hold on;
y1= x.*x/2;
plot(x, y1 , '-', 'LineWidth', 1);
hold on;
y1= cos(x)+2;
plot(x, y1 , '-', 'LineWidth', 1);
hold on;
xlim([-10 10])
ylim([-10 10])
