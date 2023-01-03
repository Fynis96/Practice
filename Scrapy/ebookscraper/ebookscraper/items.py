from scrapy import Item, Field
from itemloaders.processors import MapCompose, TakeFirst
import scrapy

def get_price(txt):
    return float(txt.replace('£', '' ))

class EbookscraperItem(scrapy.Item):
    title = Field(
        output_processor=TakeFirst()
    )
    price = Field(
        input_processor=MapCompose(get_price),
        output_processor=TakeFirst()
    )
