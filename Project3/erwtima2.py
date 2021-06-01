from __future__ import absolute_import, division, print_function, unicode_literals	# Apofugeugoume warnings (pou lunontai me downgrade tou numpy)
from warnings import simplefilter
simplefilter(action='ignore', category=FutureWarning)

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
from tensorflow.python.util import deprecation
deprecation._PRINT_DEPRECATION_WARNINGS = False

from keras.models import load_model
import pandas as pd
import numpy as np

from tensorflow.keras import backend as K

model = load_model('WindDenseNN.h5')

data = pd.read_csv('nn_representations.csv', usecols = [i for i in range(1,129)], header=None)
actual = pd.read_csv('actual.csv', usecols = [i for i in range(1,8)], header=None)
result = model.predict(data, batch_size=32)

get_layer_output = K.function(inputs = model.layers[0].input, outputs = model.layers[0].output)	# create a Keras function to get layer[0]
layer_output = get_layer_output(data)		# extract output

df1 = pd.read_csv('actual.csv', usecols=[0] , header=None)
df2 = pd.DataFrame(layer_output)

out = pd.concat([df1, df2], axis=1, ignore_index=True)
out.to_csv('new_representation.csv', index=False, header=False)
