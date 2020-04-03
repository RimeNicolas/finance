import os
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt

def create_dict_tickers(list_tickers):
    dict_tickers = dict()
    for ticker in list_tickers:
        dict_tickers[ticker] = yf.Ticker(ticker)
    return dict_tickers

def plot_stock_price(list_ticker, dict_ticker, period='ytd', a='Open'):
    for tick in list_tickers:
        hist = dict_tickers[tick].history(period)
        plt.plot(hist.index, hist[a].values)
    plt.show()

if __name__ == '__main__':
    list_tickers = [
        'MSFT',
        'AAPL',
        'SPY'
    ]
    dict_tickers = create_dict_tickers(list_tickers)
    
    sublist_tickers = list_tickers[:-1]
    plot_stock_price(list_tickers, dict_tickers)
    