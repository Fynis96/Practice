import scrapy


class EbookSpider(scrapy.Spider):
    name = 'ebook'
    start_urls = ['http://books.toscrape.com/']

    def parse(self, response):
        pass
