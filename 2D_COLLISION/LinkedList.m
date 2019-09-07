
classdef LinkedList < handle
    properties (Access = public)
        m_data;
    end
    
    methods (Access = public)
        function self = LinkedList(values)
            self.m_data = reshape(values, 1, []);
        end
        
        function Display(self)
            disp(self.m_data);
        end
        
        function Add(self, values, index)
            index = min(index, numel(self.m_data));
            self.m_data = [ self.m_data(1 : index) reshape(values, 1, []) self.m_data(index + 1 : end) ];
        end
        
        function Delete(self, index)
            self.m_data(index) = [];
        end
        
        function length = Length(self)
            length = numel(self.m_data);
        end
        
        function element = At(self, index)
            element = self.m_data(index);
        end
        
        function min = Min(self)
            if self.Length == 0
                min = [];
            else % self.Length > 0
                min = self.At(1);
                for i = 2:self.Length
                    if min > self.At(i)
                        min = self.At(i);
                    end
                end
            end
        end
    end
end
