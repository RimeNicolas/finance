import os
import numpy as np
import pandas as pd
import yfinance as yf
import scipy.optimize as sco
import matplotlib.pyplot as plt

def create_dict_tickers(list_name_tickers):
    dict_tickers = dict()
    for name_ticker in list_name_tickers:
        dict_tickers[name_ticker] = yf.Ticker(name_ticker)
    return dict_tickers

def create_dict_histories(list_name_tickers, period):
    dict_histories = dict()
    for name_ticker in list_name_tickers:
        dict_histories[name_ticker] = yf.Ticker(name_ticker).history(period)
    return dict_histories

def create_df_prices(list_name_tickers, period='ytd', cat='Open'):
    df = pd.DataFrame()
    for name_ticker in list_name_tickers:
        df.insert(loc=len(df.columns), value=yf.Ticker(name_ticker).history(period)[cat], column=name_ticker)
    return df

def plot_stock_prices(df_stocks_prices):
    i = 1
    for key, prices in df_stocks_prices.items():
        plt.figure(i, figsize=(15,5))
        i += 1
        ax1 = plt.subplot(121)
        ax1.plot(prices.index, prices.values)
        ax1.legend([key], loc=2)
        ax2 = plt.subplot(122)
        ax2.plot(prices.index[1:], np.diff(prices.values))
    plt.show()

def pf_period_return(weights, mean_returns, nb_days=252):
    return np.sum(mean_returns * weights) * (nb_days-1) 

def pf_period_std(weights, cov_matrix, nb_days=252):
    return np.sqrt(np.dot(weights.T, np.dot(cov_matrix, weights))) * np.sqrt(nb_days-1)

def pf_daily_returns(weights, df_returns, nb_days=252):
    daily_returns = np.zeros(nb_days-1)
    for i in range(len(daily_returns)):
        daily_returns[i] = weights @ df_returns.iloc[i]
    return daily_returns

def neg_sharpe_ratio(weights, mean_returns, cov_matrix, rf_rate, nb_days=252):
    pf_ret = pf_period_return(weights, mean_returns, nb_days)
    pf_std = pf_period_std(weights, cov_matrix, nb_days)
    return -(pf_ret - rf_rate) / pf_std

def max_sharpe_ratio(mean_returns, cov_matrix, rf_rate, nb_days=252, bound=(0.0,1.0)):
    num_assets = len(mean_returns)
    args = (mean_returns, cov_matrix, rf_rate, nb_days)
    constraints = ({'type': 'eq', 'fun': lambda x: np.sum(x) - 1})
    bounds = tuple(bound for asset in range(num_assets))
    return sco.minimize(neg_sharpe_ratio, num_assets*[1./num_assets,], args=args,
                        method='SLSQP', bounds=bounds, constraints=constraints)

def min_volatility(cov_matrix, nb_days=252, bound=(0.0,1.0)):
    num_assets = len(cov_matrix[0])
    args = (cov_matrix, nb_days)
    constraints = ({'type': 'eq', 'fun': lambda x: np.sum(x) - 1})
    bounds = tuple(bound for asset in range(num_assets))
    return sco.minimize(pf_period_std, num_assets*[1./num_assets,], args=args,
                        method='SLSQP', bounds=bounds, constraints=constraints)

def efficient_return(mean_returns, cov_matrix, target_return, nb_days=252, bound=(0.0,1.0)):
    num_assets = len(mean_returns)
    args = (cov_matrix, nb_days)
    constraints = ({'type': 'eq', 'fun': lambda x: pf_period_return(x, mean_returns) - target_return},
                   {'type': 'eq', 'fun': lambda x: np.sum(x) - 1})
    bounds = tuple(bound for asset in range(num_assets))
    return sco.minimize(pf_period_std, num_assets*[1./num_assets,], args=args,
                        method='SLSQP', bounds=bounds, constraints=constraints)

def efficient_frontier(mean_returns, cov_matrix, returns_range, nb_days=252, bound=(0.0,1.0)):
    efficients = []
    for ret in returns_range:
        efficients.append(efficient_return(mean_returns, cov_matrix, ret, nb_days, bound))
    return efficients

def compute_alpha_beta(df_pf_returns, market_returns, daily_returns):
    A = np.vstack([market_returns, np.ones(len(market_returns))]).T
    results = {'': ('alpha', 'beta')}
    for col in df_pf_returns.columns:
        beta, alpha = np.linalg.lstsq(A, df_pf_returns[col], rcond=None)[0]
        results[col] = (alpha, beta)
    beta, alpha = np.linalg.lstsq(A, daily_returns, rcond=None)[0]
    results['pf'] = (alpha, beta)
    df_a_b = pd.DataFrame(results)
    df_a_b = df_a_b.set_index('')
    return df_a_b

def plot_alpha_beta(df_pf_returns, market_returns, df_a_b, daily_returns):
    plt.figure(1, figsize=(15,10))
    for col in df_pf_returns.columns:
        plt.plot(market_returns, df_pf_returns[col], 'o', label='Original data '+col, markersize=2)
        plt.plot(market_returns, df_a_b[col].loc['beta'] * market_returns + df_a_b[col].loc['alpha'], label='Fitted line '+col)
    plt.plot(market_returns, daily_returns, '+', label='Original data pf returns', markersize=4)
    plt.plot(market_returns, df_a_b['pf'].loc['beta'] * market_returns + df_a_b['pf'].loc['alpha'], label='Fitted line pf returns')
    plt.xlabel('market return')
    plt.ylabel('security return')
    plt.legend(loc=2)
    plt.show()

if __name__ == '__main__':
    pass
    