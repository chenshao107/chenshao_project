# -*- coding: utf-8 -*-

import sys
from matplotlib import pyplot as plt
import pandas as pd
import requests
from bs4 import BeautifulSoup
from PyQt5.QtWidgets import QApplication, QWidget
import csv
from stock.crawl import crawl


from PyQt5.QtWidgets import QMessageBox


from ui_Widget import Ui_Widget
import xlwings as xw

class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

    ##  ==============自定义功能函数========================
    def get_stock_list(self):
        # 深交所的A股列表
        url = 'http://www.szse.cn/api/report/ShowReport?SHOWTYPE=xlsx&CATALOGID=1110&TABKEY=tab1&random=0.09339468063422496'
        r = requests.get(url, timeout=30)
        with open("A股列表.xlsx", 'wb')as fp:
            fp.write(r.content)

    def error(self):
        dlg_titile = '消息框'
        s = '出错'
        QMessageBox.warning(self, dlg_titile, s)

    def wait(self):
        dlg_titile = '消息框'
        s = '点击确认后开始爬取\n请移步\'爬取到的股票数据\'和\'爬取到的股票数据\'文件夹查看爬取数据'
        QMessageBox.about(self, dlg_titile, s)

    def print_list(self):
        wb = xw.Book('A股列表.xlsx')
        s = wb.sheets('A股列表')
        for i in range(100):

            stock_id = s.range('E{}'.format(i + 2)).value
            stock_name=s.range('B{}'.format(i + 2)).value
            if stock_id==None:
               break
            self.ui.list.append('{:}\t{:}'.format(stock_id,stock_name))

    ##  ==========由connectSlotsByName()自动连接的槽函数============
    def on_get_one_clicked(self):
        stock_code = self.ui.stock_code.text()
        print("正在爬取")
        url = 'http://quotes.money.163.com/trade/lsjysj_{0:}.html#01b07'.format(stock_code)
        try:
            r = requests.get(url)
            r.raise_for_status()
        except:
            self.error()
            return
        soup = BeautifulSoup(r.text, 'html.parser')
        stock_name = soup.find('title').text.split('历')[0]
        with open('temp.csv', 'w', newline='')as fp:
            writer = csv.writer(fp)
            data = soup.findAll('tr', {'class': 'dbrow'})
            writer.writerow(data[0].text.strip().split('\n'))
            data = soup.find('table', {"class": "table_bg001 border_box limit_sale"})

            for i in data.find_all('tr')[1:]:
                writer.writerow(list(j.text.strip() for j in i.children))

        with open('temp.csv', 'r')as fp:
            df = pd.read_csv(fp, index_col='日期')
        figure = plt.figure(figsize=(12, 8), dpi=100)  # 设定画布大小
        plt.rcParams['font.sans-serif'] = ['SimHei']  # 用于正常使用中文
        # 绘制每日新增病例柱状图
        df['开盘价'].plot(color='r', kind='line')  # 柱状图
        df['收盘价'].plot(color='blue', kind='line')  # 柱状图
        plt.title("{0:}开/收盘价变化曲线".format(stock_name), fontsize=24)
        plt.ylabel('股价', fontsize=16)
        plt.legend(["开盘价", '收盘价'])
        plt.show()

    def on_get_all_clicked(self):
        self.wait()
        crawl()


##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序

    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
