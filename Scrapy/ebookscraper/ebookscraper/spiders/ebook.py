import scrapy
from ebookscraper.items import EbookscraperItem
from scrapy.loader import ItemLoader

class EbookSpider(scrapy.Spider):
    name = 'ebook'
    start_urls = ['https://books.toscrape.com/']

    def parse(self, response):
        ebooks = response.css('article.product_pod')
        
        for ebook in ebooks:
            loader = ItemLoader(item=EbookscraperItem(), selector=ebook)
            
            loader.add_css('title', 'h3 a::attr(title)')
            loader.add_css('price', 'p.price_color::text')
            
            yield loader.load_item()
            
