#회귀모델에 사용되는 pandas, numpy, matplotlib, keras라이브러리 import
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from keras.models import Sequential
from keras.layers import LSTM, Dropout, Dense, Activation

#2015/01/01~2020/06/16 비트코인 데이터 셋을 데이터프레임으로 저장
data = pd.read_csv('bitcoin2015_2020.csv')
data.head()

#하루 동안 가장 주가가 높은 데이터를 사용
high_prices = data['High'].values

#최근 50일간의 데이터로 다음날의 주가를 예측
seq_len = 50
sequence_length = seq_len + 1
result = []
for index in range(len(high_prices) - sequence_length):
    result.append(high_prices[index: index + sequence_length])
    
#z-score 정규화(비트코인은 이상치가 있기 때문에 z-score 정규화를 사용함)
normalized_data = []
z_mean = []
z_std = []

for z in result:
    normalized_z = [((p - np.mean(z)) / np.std(z)) for p in z]
    normalized_data.append(normalized_z)
    z_mean.append(np.mean(z))
    z_std.append(np.std(z))

result = np.array(normalized_data)

#90%는 학습데이터(learning), 10%는 테스트데이터(test)로 분할
row = int(round(result.shape[0] * 0.9))
learning = result[:row, :]
np.random.shuffle(learning)

x_learning = learning[:, :-1]
x_learning = np.reshape(x_learning, (x_learning.shape[0], x_learning.shape[1], 1))
y_learning = learning[:, -1]

x_test = result[row:, :-1]
x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))
y_test = result[row:, -1]

x_learning.shape, x_test.shape

#LSTM을 이용한 회귀모델 구성(50개의 input과 1개의 output으로 모델 설계)
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(50, 1)))
model.add(LSTM(80, return_sequences=False))
model.add(Dense(1, activation='linear'))

#손실함수는 평균제곱오차(Mean Square Error), optimizer는 RMSProp
model.compile(loss='mse', optimizer='rmsprop')
model.summary()

#모델 학습(10개씩 묶어서 20번 반복학습)
model.fit(x_learning, y_learning, validation_data=(x_test, y_test), batch_size=10, epochs=20)
 
#학습시킨 모델을 사용해 예측
pred = model.predict(x_test)

#z-score 정규화 복원(그래프로 나타내기 위함)
pred_result = []
pred_y = []
for i in range(len(pred)):
    prediction = (pred[i] * z_std[i]) + z_mean[i]
    ture = (y_test[i] * z_std[i]) + z_mean[i]
    pred_result.append(prediction)
    pred_y.append(ture)

#subplot을 이용해 예측데이터와 기존데이터 그래프 한 화면에 출력
fig = plt.figure(facecolor='white', figsize=(20, 10))
plt.style.use("ggplot")
plt.rc('font',family='Malgun Gothic',size=20)
plt.title("전체데이터의 실제값과 예측값 비교")
ax = fig.add_subplot(111)
ax.plot(pred_y,"red" ,label='실제')
ax.plot(pred_result,"blue", label='예측')
ax.legend()
plt.show()

#다음날의 비트코인 주가를 예측하기 위한 최근 500개의 데이터를 사용
tomorrow_price =high_prices[-500:]
len(tomorrow_price)

#최근 50일간의 데이터로 다음날의 주가를 예측
seq_len = 50
sequence_length = seq_len + 1
result = []
for index in range(len(tomorrow_price) - sequence_length):
    result.append(tomorrow_price[index: index + sequence_length])
    
    
#z-score 정규화(비트코인은 이상치가 있기 때문에 z-score 정규화를 사용함)
normalized_data = []
z_mean = []
z_std = []

for z in result:
    normalized_z = [((p - np.mean(z)) / np.std(z)) for p in z]
    normalized_data.append(normalized_z)
    z_mean.append(np.mean(z))
    z_std.append(np.std(z))

result = np.array(normalized_data)

x_test = result[:, :-1]
x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))
y_test = result[:, -1]

x_test.shape

#학습시킨 모델을 사용해 예측
pred = model.predict(x_test)


#z-score 정규화 복원(그래프로 나타내기 위함)
pred_result = []
pred_y = []
for i in range(len(pred)):
    prediction = (pred[i] * z_std[i]) + z_mean[i]
    ture = (y_test[i] * z_std[i]) + z_mean[i]
    pred_result.append(prediction)
    pred_y.append(ture)
    
#2020/06/11~2020/06/17 비트코인 데이터 셋을 데이터프레임으로 저장(예측 데이터와 비교하기 위함)
real_data = pd.read_csv('bitcoin7days.csv')
real_result = real_data['High'].values
date = real_data['Date'].values
pred_result=pred_result[-7:]
real_result
date

#어제, 오늘과 예측한 내일의 비트코인 주가를 그래프로 출력
fig = plt.figure(facecolor='white', figsize=(20, 10))
plt.style.use("ggplot")
plt.rc('font',family='Malgun Gothic',size=20)
plt.ylabel("달러")
plt.xlabel("날짜")
plt.title("2020/06/17 비트코인 예측")
ax = fig.add_subplot(111)
ax.plot(pred_result,"blue", label='예측')
ax.plot(date,real_result,"red", label='실제')
ax.legend()
plt.show()