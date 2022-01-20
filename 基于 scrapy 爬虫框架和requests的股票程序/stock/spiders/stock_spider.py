import scrapy
import xlwings as xw
from bs4 import BeautifulSoup
import os
from matplotlib import pyplot as plt
import pandas as pd
import csv

class StockSpiderSpider(scrapy.Spider):
    name = 'stock_spider'
    start_urls = []

    def start_requests(self):
        wb = xw.Book('A股列表.xlsx')
        s = wb.sheets('A股列表')
        for i in range(10000):
            stock_id = s.range('E{}'.format(i + 2)).value
            stock_name = s.range('B{}'.format(i + 2)).value
            if stock_id == '':
                break

            url = 'http://quotes.money.163.com/trade/lsjysj_{0:}.html#01b07'.format(stock_id)
            yield scrapy.Request(
                url=url,
                meta={"stock_code": stock_id, "stock_name": stock_name},
                callback=self.parse,
            )

    def parse(self, response, **kwargs):
        soup = BeautifulSoup(response.body, 'html.parser')

        # 如果文件夹不存在，则创建
        data_fold = '爬取到的股票数据'
        if data_fold not in os.listdir(os.curdir):
            os.mkdir(data_fold)

        with open('爬取到的股票数据/{0:}{1:}.csv'.format(response.meta['stock_code'],response.meta['stock_name']), 'w', newline='')as fp:
            writer = csv.writer(fp)
            data = soup.findAll('tr', {'class': 'dbrow'})
            writer.writerow(data[0].text.strip().split('\n'))
            data = soup.find('table', {"class": "table_bg001 border_box limit_sale"})

            for i in data.find_all('tr')[1:]:
                writer.writerow(list(j.text.strip() for j in i.children))#写入数据项标题

        with open('爬取到的股票数据/{0:}{1:}.csv'.format(response.meta['stock_code'],response.meta['stock_name']), 'r')as fp:
            df = pd.read_csv(fp, index_col='日期')#以日期为索引生成二维数组

        figure = plt.figure(figsize=(12, 8), dpi=100)  # 设定画布大小
        plt.rcParams['font.sans-serif'] = ['SimHei']  # 用于正常使用中文

        # 绘制开盘价和收盘价的折线图
        df['开盘价'].plot(color='r', kind='line')  # 红色折线图
        df['收盘价'].plot(color='blue', kind='line')  # 蓝色折线图

        plt.title("{:}".format(response.meta['stock_name']), fontsize=24)#图片标题
        plt.ylabel('股价', fontsize=16)
        plt.legend(["开盘价", '收盘价'])#图例

        diagram_fold = '数据可视化表格'#保存图片的文件夹
        if diagram_fold not in os.listdir(os.curdir):#如果没有这个文件夹就创建
            os.mkdir(diagram_fold)
        fname = '{2:}/{0:}-{1:}.png'.format(response.meta['stock_code'], response.meta['stock_name'], diagram_fold)
        plt.savefig(fname)#保存图片
