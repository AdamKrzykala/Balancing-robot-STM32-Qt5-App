clear all;
close all;

f1 = figure('units','normalized','outerposition',[0 0 1 1]);
f2 = figure('units','normalized','outerposition',[0 0 1 1]);

m1 = 0.043;                % <- masa kola [kg]
m2 = 1.3;                  % <- masa wahadla [kg]
R = 0.04;                  % <- promien kola
L = 0.05;                   % <- odleglosc punktu obrotu wahadla od jego srodka masy [m]
I1 = (1/2) * m1 * R^2;     % <- moment bezwladnosci kola [kg * m^2]
I2 = (1/3) * m2 * L^2;     % <- moment bezwladnosci wahadla [kg * m^2]
g = 9.80665;               % <- przyspieszenie ziemskie [m / s^2]

% Macierz bezwladnosci
E = [m2 * R * L, m2 * L^2 + I2;
     m2 * R^2 + 2 * m1 * R^2 + 2 * I1, m2 * R * L];

% Macierz sil Coriolissa i sil odsrodkowych bezwladnosci
F = [0, 0;
     0, 0];
 
% Macierz grawitacji
G = [0, -m2 * g *L;
     0, 0];
 
% Wektor sterowania
H = [0;
     1];
 
% Macierze w rownaniu stanu

A = [0, 0, 1, 0;
     0, 0, 0, 1;
     -(E^-1)*G, -(E^-1)*F];

B = [0;
     0;
     -(E^-1)*H];

C = [1,0,0,0;
     0,1,0,0;
     0,0,1,0;
     0,0,0,1];

D = [0,0,0,0]';

% Kaskada PID

czas = 5; 

Kp1 = 0.0001;
Ki1 = 0.4;
Kd1 = 0.00001;

Kp2 = 10;
Ki2 = 100;
Kd2 = 0.1;

dTheta_0 = 0;    % <- wartosc poczatkowa predkosci kol [RPM]
dTheta_y = 0;    % <- wartosc zadana predkosci kol [RPM]

[t] = sim('Robot_PID2_model.slx',czas);

figure(f1);

subplot(3,1,1);
hold on; grid on;
title('Kat obrotu');
plot(t, Phi, 'b');
%plot(t, Theta, 'b');
xlabel('Czas [s]');
ylabel('Kat obrotu [stopnie]');
legend('Phi - kat obrotu wahadla');

subplot(3,1,2);
hold on; grid on;
title('Predkosc obrotu');
plot(t, dTheta, 'b');
%plot(t, dPhi, 'b');
xlabel('Czas [s]');
ylabel('Predkosc [RPM]');
legend('dTheta - predkosc obrotu kol');

subplot(3,1,3);
title('Pozycja');
hold on; grid on;
plot(t, X, 'b');
xlabel('Czas [s]');
ylabel('Pozycja [m]');

% Animacja robota

% Wychylenie wahadla
Phi_draw = 0;

% Pozycja kol
x1 = 0;
y1 = 0;

% Pozycja srodka masy wahadla
x2 = 0;
y2 = 0;

a_max = size(t,1);
dt = 1;
i = 1; 

for a = 0:dt:a_max-1
    
    % Obliczenie wspolrzednych
    Phi_draw = pi + ( Phi(i) * 0.01745329251 );
    
    x1 = X(i);
    y1 = R;
    
    x2 = x1 + L * sin(Phi_draw);
    y2 = y1 - L * cos(Phi_draw);
    
    % Konfiguracja wyswietlania i czyszczenie okna
    figure(f2);
    clf;
    hold on; grid on;
    %axis([-1 1 0 1]);
    axis equal;
    
    title('Animacja wychylenia robota');
    xlabel('Wspolrzedna x polozenia [m]');
    ylabel('Wspolrzedna y polozenia [m]');
        
    % Prosta imitujaca wahadlo
    plot([x1 x2],[y1 y2],'ob-');
    
    % Okrag imitujacy kola
    plot(x1 + R * cos(linspace(0,2*pi,100)),y1 + R * sin(linspace(0,2*pi,100)),'b-');
        
    display(['Czas symulacji: ' num2str(t(i))]);
        
    %xlim( x1 + 1.3 * [-2*L 2*L] );
        
    drawnow;
    
    i = i + 1;
end

display(['Koncowe polozenie robota: ' num2str(x1)]);