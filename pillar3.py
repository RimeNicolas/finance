import numpy as np 


def compute_yearly_values(init_invst, nb_years, interest_rate, increase_rate, fees_rate=0):
    ans = 0
    for i in range(nb_years):
        a = init_invst * (1+interest_rate - fees_rate)**(nb_years - i) * (1+increase_rate)**i
        # print('{:.2f}'.format(a))
        ans += a
    return ans

def compare_params():
    S = 10000
    n = 10
    r = 0.02
    s = 0.1
    print('###')
    a = compute_yearly_values(S,n,r,s)
    print('###')
    b = compute_yearly_values(S,n,0,s)
    print('###')
    print('{:.2f}'.format(a))
    print('{:.2f}'.format(b))
    print('{:.2f}'.format(a - b))

def compute_increase_rate():
    historical_values = np.array([5933, 5933, 6077, 6077,
    6192, 6192, 6365, 6365, 6566, 6566, 6682, 6682, 6739, 6739,
    6768, 6768, 6768, 6768, 6826, 6826, 6883])
    diff = np.diff(historical_values) / historical_values[:-1]
    return np.mean(diff)


def pillar3_yearly_value(nb_years):
    init_invst = 6880
    interest_rate = 0.075
    increase_rate = 0 # compute_increase_rate()
    fees_rate = 0.0071
    init_year = 2021
    print('average increase rate : {:.6f}'.format(increase_rate))
    for i in range(1, nb_years + 1):
        val = compute_yearly_values(init_invst, i, interest_rate, increase_rate, fees_rate)
        print('year {:} : {:.2f}'.format(init_year + i, val))

if __name__ == '__main__':
    pillar3_yearly_value(38)


