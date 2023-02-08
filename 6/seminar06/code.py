import pandas as pd

df = pd.read_csv('data.csv')

df = df.dropna()
df = df[(df.OBJECT_TYPE != 'AV') & (df.OBJECT_TYPE != 'AGENT')]
df = df.groupby(df.TRACK_ID).filter(lambda obj: obj.TRACK_ID.count() > 10)
df = df.groupby(df.TRACK_ID).filter(lambda obj: (obj.X.max() - obj.X.min() > 1) | (obj.Y.max() - obj.Y.min() > 1))
df.sort_values(['TRACK_ID', 'TIMESTAMP'], inplace=True)

df.to_csv('result.csv', index=False)
