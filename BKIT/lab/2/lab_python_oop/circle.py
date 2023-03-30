from lab_python_oop.figure import Figure
from lab_python_oop.figure_color import Figure_color
import math

class Circle(Figure):

    FIGURE_TYPE = 'Круг'

    @classmethod
    def get_figure_type(cls):
        return cls.FIGURE_TYPE

    def __init__(self, radius, color):
        self._radius = radius
        self._figure_color = Figure_color()
        self._figure_color.colorproperty = color

    
    def get_area(self):
        return math.pi * (self._radius ** 2)

    def __repr__(self):
        return '{} {} цвета радиусом {} площадью {}.'.format(
            Circle.get_figure_type(),
            self._figure_color.colorproperty,
            self._radius,
            self.get_area()
        )


