from scrapy.cmdline import execute

def crawl():
    execute('scrapy crawl stock_spider'.split())
