clear all

data = readtable('..\code_ultrason_ME301\arduino_log_8.csv');

times = data.Times * 10^(-3);  % Convert times to seconds (assuming they are in ms)
measures = data.Measures;

% Filter: keep only values between 10 and 17 (inclusive)
validIdx = measures >= 10 & measures <= 17;

% Apply filter
times = times(validIdx);
measures = measures(validIdx);

% Convert to numeric seconds (once!)
t = (times - times(1));  % t is now a numeric vector in seconds

% Calculate sampling frequency
dt = mean(diff(t));             % average time step in seconds
Fs = 1 / dt;                    % sampling frequency
L = length(measures);          % signal length

% Run FFT (Discrete Fourier Transform)
Y = fft(measures);

% Frequency axis
f = Fs * (0:L-1) / L;           % Frequency axis up to Nyquist

% Define color for dots and lines (e.g., blue)
lineColor = [0, 0, 1];  % RGB color (Blue)
figure;
% Plot DFT with filled dots (using scatter)
scatter(f(2:floor(L/2)), abs(Y(2:floor(L/2))), 50, lineColor, 'filled');  % Plot magnitude with filled dots

% Hold the plot to overlay vertical lines
hold on;

% Draw vertical lines at each frequency point with the same color
for i = 2:floor(L/2)  % Loop over the frequency points (scatter data)
    line([f(i), f(i)], [0, abs(Y(i))], 'Color', lineColor);  % Vertical line at each point
end

hold off;

% Add labels and title
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Discrete Fourier Transform (DFT) of Measures');
grid on;

% Define the cutoff frequency for the low-pass filter (e.g., 50 Hz)
cutoff = 3;

% Create a frequency mask for the filter
filterMask = f < cutoff;

% Apply the filter in the frequency domain by setting unwanted frequencies to zero
Y_filtered = Y' .* filterMask;

% Reconstruct the filtered signal by performing the inverse FFT
measures_filtered = ifft(Y_filtered);
figure;
% Plot the filtered signal
plot(t, measures_filtered);
title('Filtered Signal');
xlabel('Time (s)');
ylabel('Magnitude');